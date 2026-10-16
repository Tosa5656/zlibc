#ifndef ZLIBC_STRING_H
#define ZLIBC_STRING_H

#include <stddef.h>

void *memcpy(void *__restrict destination, const void *__restrict source, size_t num_bytes);
void *memmove(void *destination, const void *source, size_t num_bytes);
void *memset(void *memory_ptr, int byte_value, size_t num_bytes);
int memcmp(const void *memory1, const void *memory2, size_t num_bytes);
void *memchr(const void *memory_ptr, int target_byte, size_t num_bytes);

char *strcpy(char *__restrict destination_str, const char *__restrict source_str);
char *strncpy(char *__restrict destination_str, const char *__restrict source_str, size_t max_num_chars);
char *strcat(char *__restrict destination_str, const char *__restrict source_str);
char *strncat(char *__restrict destination_str, const char *__restrict source_str, size_t max_num_chars);
int strcmp(const char *string1, const char *string2);
int strncmp(const char *string1, const char *string2, size_t max_num_chars);
int strcoll(const char *string1, const char *string2);
size_t strxfrm(char *__restrict destination_str, const char *__restrict source_str, size_t max_num_chars);
char *strchr(const char *string_ptr, int target_char);
char *strrchr(const char *string_ptr, int target_char);
size_t strcspn(const char *string_ptr, const char *rejected_chars);
size_t strspn(const char *string_ptr, const char *accepted_chars);
char *strpbrk(const char *string_ptr, const char *accepted_chars);
char *strstr(const char *haystack_string, const char *needle_string);
char *strtok(char *__restrict string_ptr, const char *__restrict delimiter_chars);
size_t strlen(const char *string_ptr);
char *strerror(int error_number);

#endif
