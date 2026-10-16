#include <string.h>

void *memset(void *memory_ptr, int byte_value, size_t num_bytes)
{
	unsigned char *ptr = (unsigned char *)memory_ptr;
	unsigned char value = (unsigned char)byte_value;

	for (size_t i = 0; i < num_bytes; i++)
	{
		ptr[i] = value;
	}

	return memory_ptr;
}
