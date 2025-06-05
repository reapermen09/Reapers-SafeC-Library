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

#ifdef SAFEC_DEBUG
#include <stdio.h>
#define s_log(fmt, ...) fprintf(stderr, "[SafeC] " fmt "\n", ##__VA_ARGS__)
#else
#define s_log(fmt, ...)
#endif

extern void* (*s_malloc)(size_t);
extern void* (*s_realloc)(void*, size_t);
extern void  (*s_free)(void*);

char* s_strdup(const char* str);

char** s_strsplit(const char* str, char delim, size_t* out_count);

void s_strsplit_free(char** arr, size_t count);

char* s_strcat(char* dest, size_t* dest_size, const char* src);

int s_strcmp(const char* s1, const char* s2);

char* s_strcpy(char* dest, size_t dest_size, const char* src);

char* s_substr(const char* str, size_t start, size_t length);

char* s_strtrim(const char* str);

char* s_file_read(const char* filename);

int s_file_write(const char* filename, const char* data);

char* s_input(void);

void s_print(const char* fmt, ...);

void s_print_ln(const char* fmt, ...);

#endif
