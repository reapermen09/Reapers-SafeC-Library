#ifndef SAFEC_H
#define SAFEC_H

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef SAFEC_DEBUG
#define s_log(fmt, ...) fprintf(stderr, "[SafeC] " fmt "\n", ##__VA_ARGS__)
#else
#define s_log(fmt, ...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	extern void* (*s_malloc)(size_t);
	extern void* (*s_realloc)(void*, size_t);
	extern void  (*s_free)(void*);

	void s_alloc_init(void);

#ifdef __cplusplus
}
#endif

#endif
