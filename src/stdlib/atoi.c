#include <stdlib.h>

int atoi(const char *str)
{
	return (int)strtol(str, (char **)NULL, 10);
}

long atol(const char *str)
{
	return strtol(str, (char **)NULL, 10);
}

long long atoll(const char *str)
{
	return strtoll(str, (char **)NULL, 10);
}
