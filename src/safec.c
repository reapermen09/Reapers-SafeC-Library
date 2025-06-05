#include "safec.h"
#include <stdio.h>

static void* s_default_malloc(size_t size) { return malloc(size); }
static void* s_default_realloc(void* ptr, size_t size) { return realloc(ptr, size); }
static void  s_default_free(void* ptr) { free(ptr); }

void* (*s_malloc)(size_t) = NULL;
void* (*s_realloc)(void*, size_t) = NULL;
void  (*s_free)(void*) = NULL;

void s_alloc_init(void) {
    if (!s_malloc) s_malloc = s_default_malloc;
    if (!s_realloc) s_realloc = s_default_realloc;
    if (!s_free) s_free = s_default_free;
}
