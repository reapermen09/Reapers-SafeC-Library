#include "safec.h"
#include "io.h"
#include <stdio.h>
#include <stdarg.h>

char* s_input(void) {
    size_t size = 64;
    size_t len = 0;
    char* buffer = (char*)s_malloc(size);
    if (!buffer) return NULL;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char* temp = (char*)s_realloc(buffer, size);
            if (!temp) {
                s_free(buffer);
                return NULL;
            }
            buffer = temp;
        }
        buffer[len++] = (char)ch;
    }

    if (len == 0 && ch == EOF) {
        s_free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

static void s_vprint_internal(const char* fmt, int add_newline, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);

    int size = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);

    if (size < 0) return;

    size_t buffer_size = (size_t)size + 1 + (add_newline ? 1 : 0);
    char* buffer = (char*)s_malloc(buffer_size);
    if (!buffer) return;

    vsnprintf(buffer, (size_t)size + 1, fmt, args);

    if (add_newline) {
        buffer[size] = '\n';
        buffer[size + 1] = '\0';
    }

    fputs(buffer, stdout);
    s_free(buffer);
}

void s_print(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    s_vprint_internal(fmt, 0, args);
    va_end(args);
}

void s_print_ln(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    s_vprint_internal(fmt, 1, args);
    va_end(args);
}