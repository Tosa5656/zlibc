#ifndef ZLIBC_TEST_H
#define ZLIBC_TEST_H

#include <stdio.h>

extern int test_checks;
extern int test_failures;
extern int test_passed;
extern int test_failed;

void test_suite(const char *name);
void test_finish(void);
void test_summary(void);
void test_fail(const char *file, int line, const char *format, ...);
int test_streq(const char *string1, const char *string2);
int test_bytes_eq(const void *bytes1, const void *bytes2, size_t count);
int test_bytes_all(const void *bytes, unsigned char value, size_t count);

#define CHECK(condition) \
	do \
	{ \
		test_checks++; \
		if (!(condition)) \
		{ \
			test_fail(__FILE__, __LINE__, "%s", #condition); \
		} \
	} while (0)

#define CHECK_STR(actual, expected) \
	do \
	{ \
		const char *actual_value = (actual); \
		test_checks++; \
		if (actual_value == NULL || !test_streq(actual_value, (expected))) \
		{ \
			test_fail(__FILE__, __LINE__, "%s: got \"%s\", want \"%s\"", \
				#actual, actual_value == NULL ? "(null)" : actual_value, (expected)); \
		} \
	} while (0)

#define CHECK_SIZE(actual, expected) \
	do \
	{ \
		size_t actual_value = (size_t)(actual); \
		size_t expected_value = (size_t)(expected); \
		test_checks++; \
		if (actual_value != expected_value) \
		{ \
			test_fail(__FILE__, __LINE__, "%s: got %zu, want %zu", \
				#actual, actual_value, expected_value); \
		} \
	} while (0)

#define CHECK_INT(actual, expected) \
	do \
	{ \
		long actual_value = (long)(actual); \
		long expected_value = (long)(expected); \
		test_checks++; \
		if (actual_value != expected_value) \
		{ \
			test_fail(__FILE__, __LINE__, "%s: got %ld, want %ld", \
				#actual, actual_value, expected_value); \
		} \
	} while (0)

#define CHECK_SIGN(actual, expected) \
	do \
	{ \
		long actual_value = (long)(actual); \
		long expected_value = (long)(expected); \
		int actual_sign = (actual_value > 0) - (actual_value < 0); \
		int expected_sign = (expected_value > 0) - (expected_value < 0); \
		test_checks++; \
		if (actual_sign != expected_sign) \
		{ \
			test_fail(__FILE__, __LINE__, "%s: got %ld, want sign %ld", \
				#actual, actual_value, expected_value); \
		} \
	} while (0)

#define CHECK_PTR(actual, expected) \
	do \
	{ \
		const void *actual_value = (const void *)(actual); \
		const void *expected_value = (const void *)(expected); \
		test_checks++; \
		if (actual_value != expected_value) \
		{ \
			test_fail(__FILE__, __LINE__, "%s: got %p, want %p", \
				#actual, actual_value, expected_value); \
		} \
	} while (0)

#endif
