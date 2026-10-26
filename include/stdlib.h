#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

#include <alltypes.h>

int atoi(const char *str);
long atol(const char *str);
long long atoll(const char *str);
double atof(const char *str);

float strtof(const char *__restrict nptr, char **__restrict endptr);
double strtod(const char *__restrict nptr, char **__restrict endptr);
long double strtold(const char *__restrict nptr, char **__restrict endptr);

long strtol(const char *__restrict nptr, char **__restrict endptr, int base);
unsigned long strtoul(const char *__restrict nptr, char **__restrict endptr, int base);
long long strtoll(const char *__restrict nptr, char **__restrict endptr, int base);
unsigned long long strtoull(const char *__restrict nptr, char **__restrict endptr, int base);

int rand(void);
void srand(unsigned int seed);

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void *aligned_alloc(size_t alignment, size_t size);

_Noreturn void abort(void);
int atexit(void (*func)(void));
_Noreturn void exit(int status);
_Noreturn void _Exit(int status);
int at_quick_exit(void (*func)(void));
_Noreturn void quick_exit(int status);

//char *getenv(const char *name);
//int system(const char *command);

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

int abs(int j);
long labs(long j);
long long llabs(long long j);

typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;
typedef struct { long long quot, rem; } lldiv_t;

div_t div(int numer, int denom);
ldiv_t ldiv(long numer, long denom);
lldiv_t lldiv(long long numer, long long denom);

int mblen(const char *s, size_t n);
int mbtowc(wchar_t *__restrict pwc, const char *__restrict s, size_t n);
int wctomb(char *s, wchar_t wchar);
size_t mbstowcs(wchar_t *__restrict pwcs, const char *__restrict s, size_t n);
size_t wcstombs(char *__restrict s, const wchar_t *__restrict pwcs, size_t n);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

size_t __ctype_get_mb_cur_max(void);
#define MB_CUR_MAX (__ctype_get_mb_cur_max())

#define RAND_MAX (0x7fffffff)

#endif
