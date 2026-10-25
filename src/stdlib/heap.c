#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/syscall.h>
#include "heap.h"

#define HEAP_HEADER_SIZE	sizeof(block_t)
#define HEAP_USED_FLAG		((size_t)1)
#define HEAP_MIN_PAYLOAD	((size_t)16)

typedef struct block
{
	size_t size;
	struct block *next;
} block_t;

static block_t *heap_list = NULL;
static block_t *heap_tail = NULL;

static size_t heap_payload_of(const block_t *block)
{
	return block->size & ~HEAP_USED_FLAG;
}

static size_t heap_align_up(size_t num_bytes)
{
	return (num_bytes + (HEAP_MIN_PAYLOAD - 1)) & ~(HEAP_MIN_PAYLOAD - 1);
}

static uintptr_t heap_ptr_align_up(uintptr_t address, size_t alignment)
{
	return (address + alignment - 1) & ~((uintptr_t)alignment - 1);
}

static uintptr_t heap_block_end(const block_t *block)
{
	return (uintptr_t)block + HEAP_HEADER_SIZE + (block->size & ~HEAP_USED_FLAG);
}

static int heap_is_used(const block_t *block)
{
	return (block->size & HEAP_USED_FLAG) != 0;
}

static block_t *heap_locate(const void *user_ptr, block_t **previous_out)
{
	unsigned char *header = (unsigned char *)user_ptr - HEAP_HEADER_SIZE;
	block_t *previous = NULL;
	block_t *block;

	for (block = heap_list; block != NULL; previous = block, block = block->next)
	{
		if ((block_t *)header == block)
		{
			if (previous_out)
			{
				*previous_out = previous;
			}
			return block;
		}
	}

	return NULL;
}

static void heap_merge_forward(block_t *block)
{
	block_t *next = block->next;

	if (next && !heap_is_used(next) && heap_block_end(block) == (uintptr_t)next)
	{
		block->size += HEAP_HEADER_SIZE + next->size;
		block->next = next->next;

		if (heap_tail == next)
		{
			heap_tail = block;
		}
	}
}

static int heap_extend(size_t payload)
{
	uintptr_t current = (uintptr_t)__syscall1(SYSCALL_BRK, 0);
	uintptr_t target;
	uintptr_t base;
	block_t *block;
	block_t *tail = heap_tail;

	if (current == (uintptr_t)-1)
	{
		return 0;
	}

	if (tail && !heap_is_used(tail) && heap_block_end(tail) == current)
	{
		if (current + payload < current)
		{
			return 0;
		}

		target = current + payload;

		if ((uintptr_t)__syscall1(SYSCALL_BRK, (long)target) != target)
		{
			return 0;
		}

		tail->size += payload;
		return 1;
	}

	if (current + payload + HEAP_HEADER_SIZE < current)
	{
		return 0;
	}

	target = heap_ptr_align_up(current + payload + HEAP_HEADER_SIZE, HEAP_MIN_PAYLOAD);

	if ((uintptr_t)__syscall1(SYSCALL_BRK, (long)target) != target)
	{
		return 0;
	}

	base = heap_align_up(current);
	block = (block_t *)base;

	block->size = (size_t)((uintptr_t)target - base) - HEAP_HEADER_SIZE;

	if (tail)
	{
		tail->next = block;
	}
	else
	{
		heap_list = block;
	}
	heap_tail = block;

	return 1;
}

static block_t *heap_split(block_t *block, size_t payload)
{
	size_t payload_now = heap_payload_of(block);

	if (payload_now >= payload + HEAP_HEADER_SIZE + HEAP_MIN_PAYLOAD)
	{
		block_t *rest = (block_t *)((uintptr_t)block + HEAP_HEADER_SIZE + payload);

		rest->size = payload_now - payload - HEAP_HEADER_SIZE;
		rest->next = block->next;

		block->next = rest;
		block->size = payload;

		if (heap_tail == block)
		{
			heap_tail = rest;
		}

		return rest;
	}

	return NULL;
}

static void heap_claim(block_t *block, size_t payload)
{
	heap_split(block, payload);
	block->size = payload | HEAP_USED_FLAG;
}

void *__libc_heap_alloc(size_t num_bytes)
{
	size_t request;
	block_t *block;

	if (num_bytes == 0)
	{
		return NULL;
	}

	if (num_bytes > ((size_t)-1) / 2)
	{
		return NULL;
	}

	request = heap_align_up(num_bytes);
	if (request < num_bytes)
	{
		return NULL;
	}

	for (block = heap_list; block != NULL; block = block->next)
	{
		if (!heap_is_used(block) && heap_payload_of(block) >= request)
		{
			heap_claim(block, request);
			return (unsigned char *)block + HEAP_HEADER_SIZE;
		}
	}

	if (heap_extend(request))
	{
		block = heap_tail;

		if (heap_payload_of(block) >= request)
		{
			heap_claim(block, request);
			return (unsigned char *)block + HEAP_HEADER_SIZE;
		}
	}

	return NULL;
}

void __libc_heap_release(void *old_ptr)
{
	block_t *previous = NULL;
	block_t *block;

	if (old_ptr == NULL)
	{
		return;
	}

	block = heap_locate(old_ptr, &previous);
	if (block == NULL || heap_is_used(block) == 0)
	{
		return;
	}

	block->size &= ~HEAP_USED_FLAG;

	heap_merge_forward(block);

	if (previous && !heap_is_used(previous) &&
		heap_block_end(previous) == (uintptr_t)block)
	{
		previous->size += HEAP_HEADER_SIZE + (block->size & ~HEAP_USED_FLAG);
		previous->next = block->next;

		if (heap_tail == block)
		{
			heap_tail = previous;
		}
	}
}

void *__libc_heap_alloc_aligned(size_t alignment, size_t num_bytes)
{
	size_t request;
	size_t reserve;
	unsigned char *raw_ptr;
	block_t *gap;
	block_t *aligned_block;
	block_t *previous = NULL;
	uintptr_t anchor;

	if (num_bytes == 0)
	{
		return NULL;
	}

	if (alignment < HEAP_MIN_PAYLOAD)
	{
		alignment = HEAP_MIN_PAYLOAD;
	}

	if (alignment & (alignment - 1))
	{
		return NULL;
	}

	if (num_bytes > ((size_t)-1) / 2)
	{
		return NULL;
	}

	request = heap_align_up(num_bytes);
	if (request < num_bytes)
	{
		return NULL;
	}

	reserve = request + 2 * HEAP_HEADER_SIZE + HEAP_MIN_PAYLOAD + alignment;
	if (reserve < request)
	{
		return NULL;
	}

	raw_ptr = __libc_heap_alloc(reserve);
	if (raw_ptr == NULL)
	{
		return NULL;
	}

	if ((uintptr_t)raw_ptr % alignment == 0)
	{
		return raw_ptr;
	}

	gap = (block_t *)(raw_ptr - HEAP_HEADER_SIZE);

	anchor = heap_ptr_align_up((uintptr_t)gap + 2 * HEAP_HEADER_SIZE + HEAP_MIN_PAYLOAD, alignment);

	gap->size = (size_t)(anchor - (uintptr_t)gap) - 2 * HEAP_HEADER_SIZE;
	gap->size &= ~HEAP_USED_FLAG;

	aligned_block = (block_t *)(anchor - HEAP_HEADER_SIZE);
	aligned_block->size = request | HEAP_USED_FLAG;
	aligned_block->next = gap->next;
	gap->next = aligned_block;

	if (heap_tail == gap && aligned_block->next == NULL)
	{
		heap_tail = aligned_block;
	}

	heap_locate((unsigned char *)gap + HEAP_HEADER_SIZE, &previous);
	if (previous && !heap_is_used(previous) && heap_block_end(previous) == (uintptr_t)gap)
	{
		previous->size += HEAP_HEADER_SIZE + gap->size;
		previous->next = gap->next;

		if (heap_tail == gap)
		{
			heap_tail = previous;
		}
	}

	return (unsigned char *)aligned_block + HEAP_HEADER_SIZE;
}

void *__libc_heap_resize(void *old_ptr, size_t num_bytes)
{
	size_t request;
	block_t *previous = NULL;
	block_t *block;
	block_t *rest;

	if (old_ptr == NULL)
	{
		return __libc_heap_alloc(num_bytes);
	}

	if (num_bytes == 0)
	{
		__libc_heap_release(old_ptr);
		return NULL;
	}

	if (num_bytes > ((size_t)-1) / 2)
	{
		return NULL;
	}

	request = heap_align_up(num_bytes);
	if (request < num_bytes)
	{
		return NULL;
	}

	block = heap_locate(old_ptr, &previous);
	if (block == NULL || heap_is_used(block) == 0)
	{
		return NULL;
	}

	if (heap_payload_of(block) >= request)
	{
		rest = heap_split(block, request);
		block->size = request | HEAP_USED_FLAG;

		if (rest)
		{
			heap_merge_forward(rest);
		}

		return old_ptr;
	}

	if (block->next && !heap_is_used(block->next) && heap_block_end(block) == (uintptr_t)block->next && heap_payload_of(block) + HEAP_HEADER_SIZE + heap_payload_of(block->next) >= request)
	{
		if (heap_tail == block->next)
		{
			heap_tail = block;
		}

		block->size += HEAP_HEADER_SIZE + heap_payload_of(block->next);
		block->next = block->next->next;

		rest = heap_split(block, request);
		block->size = request | HEAP_USED_FLAG;

		if (rest)
		{
			heap_merge_forward(rest);
		}

		return old_ptr;
	}

	void *fresh_ptr = __libc_heap_alloc(num_bytes);
	size_t copy_bytes;

	if (fresh_ptr == NULL)
	{
		return NULL;
	}

	copy_bytes = heap_payload_of(block);
	if (copy_bytes > num_bytes)
	{
		copy_bytes = num_bytes;
	}

	memcpy(fresh_ptr, old_ptr, copy_bytes);
	__libc_heap_release(old_ptr);

	return fresh_ptr;
}
