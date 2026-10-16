#include <string.h>

int memcmp(const void *memory1, const void *memory2, size_t num_bytes)
{
	const unsigned char *ptr1 = (const unsigned char *)memory1;
	const unsigned char *ptr2 = (const unsigned char *)memory2;

	for (size_t i = 0; i < num_bytes; i++)
	{
		if (ptr1[i] != ptr2[i])
		{
			return (ptr1[i] < ptr2[i]) ? -1 : 1;
		}
	}

	return 0;
}
