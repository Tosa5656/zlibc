#ifndef _CTYPE_H
#define _CTYPE_H

#include <alltypes.h>

int isalnum(int target_char);
int isalpha(int target_char);
int isblank(int target_char);
int iscntrl(int target_char);
int isdigit(int target_char);
int isgraph(int target_char);
int islower(int target_char);
int isprint(int target_char);
int ispunct(int target_char);
int isspace(int target_char);
int isupper(int target_char);
int isxdigit(int target_char);
int tolower(int target_char);
int toupper(int target_char);

#endif
