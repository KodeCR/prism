/* Ignite */
#ifndef LIBC_H
#define LIBC_H

#include <stddef.h>

extern char __heap_start[];
extern char __heap_end[];

int printf(const char *fmt, ...);
int scanf(const char *fmt, ...);
void* malloc(size_t size);
void *memset(void *m, int c, size_t n);
char* strcpy(char* dst, const char* src);
int strcmp(const char *s1, const char *s2);

#endif /* LIBC_H */