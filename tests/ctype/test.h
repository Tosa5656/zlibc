#ifndef ZLIBC_CTYPE_TEST_H
#define ZLIBC_CTYPE_TEST_H

#include "../test.h"
#include "../../include/ctype.h"

void test_ctype(void);

void test_ctype_class(const char *function_name, int (*function)(int), const int *ranges, size_t range_count);

void test_ctype_case(const char *function_name, int (*function)(int), const int *ranges, size_t range_count, int offset);

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
