/* Ignite */
// mostly from picolibc/newlib
#include "libc.h"
#include "../uart/uart.h"
// #include <stdio.h>
typedef unsigned long uintptr_t;
#include <stdarg.h>
#include <limits.h>

int scanf(const char *fmt, ...) {
    va_list ap;
    int i = 0;
    int *n;
    char c;

    va_start(ap, fmt);
    if (*fmt == '%' && *(++fmt) == 'd') {
      while ((c = uart_receive()) != '\r') {
        if (c < '0' || c > '9') {
          continue;
        }
        i *= 10;
        i += (c - '0');
        uart_transmit(c);
      }
    }
    va_end(ap);
    n = va_arg(ap, int *);
    *n = i;
    return i;
}

void* malloc(size_t size) {
    static char * heap = 0;
    void* alloc;
    if (heap == 0) { heap = __heap_start; }
    alloc = heap;
    heap += size;
    if (heap > __heap_end) { return NULL; } else { return alloc; }
}

#define LBLOCKSIZE (sizeof(long))
#define UNALIGNED(X)   ((uintptr_t)X & (LBLOCKSIZE - 1))
#define TOO_SMALL(LEN) ((LEN) < LBLOCKSIZE)
void *memset(void *m, int c, size_t n) {
//   char *s = (char *)m;
//   while (n--)
//     *s++ = (char)c;
//   return m;
  char *s = (char *)m;
  unsigned int i;
  unsigned long buffer;
  unsigned long *aligned_addr;
  unsigned int d = c & 0xff; /* To avoid sign extension, copy C to an unsigned variable.  */

  while (UNALIGNED(s)) {
    if (n--)
      *s++ = (char)c;
    else
      return m;
  }

  if (!TOO_SMALL(n)) {
    /* If we get this far, we know that n is large and s is word-aligned. */
    aligned_addr = (unsigned long *)s;

    /* Store D into each char sized location in BUFFER so that
       we can set large blocks quickly.  */
    buffer = (d << 8) | d;
    buffer |= (buffer << 16);
    for (i = 32; i < LBLOCKSIZE * 8; i <<= 1)
      buffer = (buffer << i) | buffer;

    /* Unroll the loop.  */
    while (n >= LBLOCKSIZE * 4) {
      *aligned_addr++ = buffer;
      *aligned_addr++ = buffer;
      *aligned_addr++ = buffer;
      *aligned_addr++ = buffer;
      n -= 4 * LBLOCKSIZE;
    }

    while (n >= LBLOCKSIZE) {
      *aligned_addr++ = buffer;
      n -= LBLOCKSIZE;
    }
    /* Pick up the remainder with a bytewise loop.  */
    s = (char *)aligned_addr;
  }
  return m;
}

/* Nonzero if either X or Y is not aligned on a "long" boundary.  */
#define UNALIGNED2(X, Y) (((long)X & (sizeof(long) - 1)) | ((long)Y & (sizeof(long) - 1)))
/* DETECTNULL returns nonzero if (long)X contains a NULL byte. */
#if LONG_MAX == 2147483647L
#define DETECTNULL(X) (((X)-0x01010101) & ~(X)&0x80808080)
#else
#if LONG_MAX == 9223372036854775807L
#define DETECTNULL(X) (((X)-0x0101010101010101) & ~(X)&0x8080808080808080)
#else
#error long int is not a 32bit or 64bit type.
#endif
#endif
char* strcpy(char* dst, const char* src) {
//   char *s = dst;
//   while ((*dst++ = *src++))
//     ;
//   return s;
  char* _dst = dst;
  const char* _src = src;
  long* aligned_dst;
  const long* aligned_src;

  /* If SRC or DEST is unaligned, then copy bytes.  */
  if (!UNALIGNED2(_src, _dst)) {
    aligned_dst = (long *)_dst;
    aligned_src = (long *)_src;

    /* SRC and DEST are both "long int" aligned, try to do "long int" sized copies.  */
    while (!DETECTNULL(*aligned_src)) {
      *aligned_dst++ = *aligned_src++;
    }

    _dst = (char *)aligned_dst;
    _src = (char *)aligned_src;
  }

  while ((*_dst++ = *_src++))
    ;
  return dst;
}

int strcmp(const char *s1, const char *s2) {
//   while (*s1 != '\0' && *s1 == *s2) {
//     s1++;
//     s2++;
//   }
//   return (*(unsigned char *)s1) - (*(unsigned char *)s2);
  unsigned long *a1;
  unsigned long *a2;

  /* If s1 or s2 are unaligned, then compare bytes. */
  if (!UNALIGNED2(s1, s2)) {
    /* If s1 and s2 are word-aligned, compare them a word at a time. */
    a1 = (unsigned long *)s1;
    a2 = (unsigned long *)s2;
    while (*a1 == *a2) {
      /* To get here, *a1 == *a2, thus if we find a null in *a1,
         then the strings must be equal, so return zero.  */
      if (DETECTNULL(*a1))
        return 0;

      a1++;
      a2++;
    }

    /* A difference was detected in last few bytes of s1, so search bytewise */
    s1 = (char *)a1;
    s2 = (char *)a2;
  }

  while (*s1 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
  }
  return (*(unsigned char *)s1) - (*(unsigned char *)s2);
}

#include "ee_printf.c"
#if HAS_FLOAT
#include "cvt.c"
#include "modf.c"
#endif