/*
 * SafeC Library made for C
 *
 * Author: Reapermen
 * License: MIT
 *
 * safec.h and safec.c are released under the MIT License.
 */

#ifndef SAFEC_H
#define SAFEC_H

#include <stddef.h>

char* s_input(void);

void s_print(const char* fmt, ...);

void s_print_ln(const char* fmt, ...);

char* s_strdup(const char* str);

char* s_strcat(char* dest, size_t* dest_size, const char* src);

int s_strcmp(const char* s1, const char* s2);

char* s_strcpy(char* dest, size_t dest_size, const char* src);

char* s_substr(const char* str, size_t start, size_t length);

char* s_strtrim(const char* str);

char** s_strsplit(const char* str, char delim, size_t* out_count);

void s_strsplit_free(char** arr, size_t count);

#endif
