#ifndef SAFEC_IO_H
#define SAFEC_IO_H

static void s_vprint_internal(const char* fmt, int add_newline, va_list args);

char* s_input(void);

void s_print(const char* fmt, ...);

void s_print_ln(const char* fmt, ...);

#endif