#ifndef LIBC_H
#define LIBC_H

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

void* malloc(size_t size);
void free(void* ptr);
void* alloc_aligned(size_t size, void* allocator, size_t alignment);

int strcmp(const char* str1, const char* str2);
void* memcpy(void* destination, const void* source, size_t num);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
void* memset(void* ptr, size_t num, int value);
#pragma GCC diagnostic pop

#ifdef __cplusplus
#define CHAR16_TYPE char16_t
#else
#define CHAR16_TYPE __CHAR16_TYPE__
#endif

CHAR16_TYPE* wcsncpy(CHAR16_TYPE* destination, const CHAR16_TYPE* source, size_t num);

size_t  wcslen(const CHAR16_TYPE* wcs);
CHAR16_TYPE* wcscat(CHAR16_TYPE* destination, const CHAR16_TYPE* source);

int swprintf(CHAR16_TYPE* ws, size_t len, const CHAR16_TYPE* format, ...);

#ifdef __cplusplus
}
#endif

#endif
