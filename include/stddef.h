#ifndef _STDDEF_H
#define _STDDEF_H

#ifndef _SIZE_T
#define _SIZE_T
typedef __SIZE_TYPE__ size_t;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef __WCHAR_TYPE__ wchar_t;
#endif

#undef NULL
#if defined(__cplusplus)
#define NULL 0L
#else
#define NULL ((void *)0)
#endif

#undef offsetof
#define offsetof(type, member) __builtin_offsetof(type, member)

#endif
