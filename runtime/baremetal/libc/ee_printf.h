/* Ignite */
#ifndef __EE_PRINTF_H__
#define __EE_PRINTF_H__

#include <stddef.h>
#include <stdarg.h>
#include "../uart/uart.h"

typedef size_t         ee_size_t;
#ifndef HAS_FLOAT
#define HAS_FLOAT 0
#endif

int ee_vprintf(const char *fmt, va_list args);

int ee_printf ( const char * format, ... )
{
  int n;
  va_list args;
  va_start (args, format);
  n = ee_vprintf (format, args);
  va_end (args);
  return n;
}

int printf ( const char * format, ... )
{
  int n;
  va_list args;
  va_start (args, format);
  n = ee_vprintf (format, args);
  va_end (args);
  return n;
}


#define uart_send_char uart_transmit

#endif /* __EE_PRINTF_H__ */
