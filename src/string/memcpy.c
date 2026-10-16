#include <string.h>

void *memcpy(void *__restrict destination, const void *__restrict source, size_t num_bytes)
{
	unsigned char *dest_ptr = (unsigned char *)destination;
	const unsigned char *src_ptr = (const unsigned char *)source;

	for (size_t i = 0; i < num_bytes; i++)
	{
		dest_ptr[i] = src_ptr[i];
	}

	return destination;
}
