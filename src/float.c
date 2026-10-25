#include <float.h>
#include <stdint.h>

int __flt_rounds(void)
{
	uint32_t mxcsr = 0;

	__asm__ __volatile__ ("stmxcsr %0" : "=m"(mxcsr));


	uint32_t mode = (mxcsr >> 13) & 3;

	static const int round_modes[] = { 1, 3, 2, 0 };

	return round_modes[mode];
}
