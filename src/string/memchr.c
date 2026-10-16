#include <string.h>

void *memchr(const void *memory_ptr, int target_byte, size_t num_bytes)
{
	const unsigned char *ptr = (const unsigned char *)memory_ptr;
	unsigned char value = (unsigned char)target_byte;

	for (size_t i = 0; i < num_bytes; i++)
	{
		if (ptr[i] == value)
		{
			return (void *)(ptr + i);
		}
	}

	return NULL;
}
