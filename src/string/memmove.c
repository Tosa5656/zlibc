#include <string.h>

void *memmove(void *destination, const void *source, size_t num_bytes)
{
	unsigned char *destination_ptr = (unsigned char *)destination;
	const unsigned char *source_ptr = (const unsigned char *)source;

	if(destination_ptr == source_ptr || num_bytes == 0)
	{
		return destination;
	}

	if(destination_ptr > source_ptr && destination_ptr < source_ptr + num_bytes)
	{
		for (size_t i = num_bytes; i > 0; i--)
		{
			destination_ptr[i - 1] = source_ptr[i - 1];
		}
	}
	else
	{
		for (size_t i = 0; i < num_bytes; i++)
		{
			destination_ptr[i] = source_ptr[i];
		}
	}

	return destination;
}
