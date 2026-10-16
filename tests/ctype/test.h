#ifndef ZLIBC_CTYPE_TEST_H
#define ZLIBC_CTYPE_TEST_H

#include "../test.h"
#include "../../include/ctype.h"

void test_ctype(void);

/*
 * Checks a character classification function over EOF (-1) and every byte
 * value (0..255). The expected result is nonzero when the value falls into
 * one of the inclusive [low, high] ranges in "ranges" (stored as
 * { low0, high0, low1, high1, ... }) and zero otherwise.
 */
void test_ctype_class(const char *function_name, int (*function)(int),
	const int *ranges, size_t range_count);

/*
 * Checks a case conversion function over EOF (-1) and every byte value
 * (0..255). Values inside "ranges" are expected to be shifted by "offset",
 * every other value must be returned unchanged.
 */
void test_ctype_case(const char *function_name, int (*function)(int),
	const int *ranges, size_t range_count, int offset);

void test_isalnum(void);
void test_isalpha(void);
void test_isblank(void);
void test_iscntrl(void);
void test_isdigit(void);
void test_isgraph(void);
void test_islower(void);
void test_isprint(void);
void test_ispunct(void);
void test_isspace(void);
void test_isupper(void);
void test_isxdigit(void);
void test_tolower(void);
void test_toupper(void);

#endif
