#include "safec.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void* (*s_malloc)(size_t) = malloc;
void* (*s_realloc)(void*, size_t) = realloc;
void  (*s_free)(void*) = free;

char* s_strdup(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* dup = s_malloc(len + 1);
    if (!dup) return NULL;
    memcpy(dup, str, len + 1);
    s_log("s_strdup allocated %zu bytes", len + 1);
    return dup;
}

char** s_strsplit(const char* str, char delim, size_t* out_count) {
    if (!str) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    size_t count = 1;
    for (const char* p = str; *p; p++) {
        if (*p == delim) count++;
    }

    char** result = s_malloc(sizeof(char*) * count);
    if (!result) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    size_t idx = 0;
    const char* start = str;
    for (const char* p = str; ; p++) {
        if (*p == delim || *p == '\0') {
            size_t len = p - start;
            char* token = s_malloc(len + 1);
            if (!token) {
                for (size_t i = 0; i < idx; i++) {
                    s_free(result[i]);
                }
                s_free(result);
                if (out_count) *out_count = 0;
                return NULL;
            }
            memcpy(token, start, len);
            token[len] = '\0';
            result[idx++] = token;

            if (*p == '\0') break;
            start = p + 1;
        }
    }

    if (out_count) *out_count = count;
    return result;
}

void s_strsplit_free(char** arr, size_t count) {
    if (!arr) return;
    for (size_t i = 0; i < count; i++) {
        s_free(arr[i]);
    }
    s_free(arr);
}

char* s_strcat(char* dest, size_t* dest_size, const char* src) {
    if (!src || !dest_size) return NULL;

    size_t src_len = strlen(src);

    if (!dest || *dest_size == 0) {
        size_t new_size = src_len + 1;
        char* new_buf = s_malloc(new_size);
        if (!new_buf) return NULL;
        memcpy(new_buf, src, src_len + 1);
        *dest_size = new_size;
        s_log("s_strcat allocated new buffer of size %zu", new_size);
        return new_buf;
    }

    size_t dest_len = strlen(dest);
    size_t needed = dest_len + src_len + 1;

    if (needed > *dest_size) {
        size_t new_size = needed + 32;
        char* temp = s_realloc(dest, new_size);
        if (!temp) return NULL;
        dest = temp;
        *dest_size = new_size;
        s_log("s_strcat reallocated buffer to size %zu", new_size);
    }

    memcpy(dest + dest_len, src, src_len + 1);
    return dest;
}

int s_strcmp(const char* s1, const char* s2) {
    if (!s1 && !s2) return 0;
    if (!s1) return -1;
    if (!s2) return 1;
    return strcmp(s1, s2);
}

char* s_strcpy(char* dest, size_t dest_size, const char* src) {
    if (!dest || !src || dest_size == 0) return NULL;

    size_t src_len = strlen(src);
    if (src_len + 1 > dest_size) {
        // Truncate safely
        memcpy(dest, src, dest_size - 1);
        dest[dest_size - 1] = '\0';
        s_log("s_strcpy truncated input to fit buffer size %zu", dest_size);
        return dest;
    }
    memcpy(dest, src, src_len + 1);
    return dest;
}

char* s_substr(const char* str, size_t start, size_t length) {
    if (!str) return NULL;
    size_t str_len = strlen(str);
    if (start >= str_len) {
        char* empty = s_malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }
    if (start + length > str_len) {
        length = str_len - start;
    }
    char* sub = s_malloc(length + 1);
    if (!sub) return NULL;
    memcpy(sub, str + start, length);
    sub[length] = '\0';
    return sub;
}

char* s_strtrim(const char* str) {
    if (!str) return NULL;

    const char* start = str;
    while (*start && isspace((unsigned char)*start)) start++;

    if (*start == '\0') {
        char* empty = s_malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }

    const char* end = str + strlen(str);
    while (end > start && isspace((unsigned char)*(end - 1))) end--;

    size_t len = end - start;
    char* trimmed = s_malloc(len + 1);
    if (!trimmed) return NULL;
    memcpy(trimmed, start, len);
    trimmed[len] = '\0';
    return trimmed;
}

char* s_input(void) {
    size_t size = 64;
    size_t len = 0;
    char* buffer = s_malloc(size);
    if (!buffer) return NULL;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char* temp = s_realloc(buffer, size);
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

void s_print(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    if (size < 0) return;

    char* buffer = s_malloc((size_t)size + 1);
    if (!buffer) return;

    va_start(args, fmt);
    vsnprintf(buffer, (size_t)size + 1, fmt, args);
    va_end(args);

    fputs(buffer, stdout);
    s_free(buffer);
}

void s_print_ln(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    if (size < 0) return;

    char* buffer = s_malloc((size_t)size + 1);
    if (!buffer) return;

    va_start(args, fmt);
    vsnprintf(buffer, (size_t)size + 1, fmt, args);
    va_end(args);

    fputs(buffer, stdout);
    putchar('\n');
    s_free(buffer);
}

char* s_file_read(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        s_log("s_file_read: Failed to open file '%s'", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    if (size < 0) {
        fclose(file);
        s_log("s_file_read: ftell error for file '%s'", filename);
        return NULL;
    }

    char* buffer = s_malloc((size_t)size + 1);
    if (!buffer) {
        fclose(file);
        s_log("s_file_read: malloc failed for size %ld", size + 1);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, (size_t)size, file);
    fclose(file);
    if (read_size != (size_t)size) {
        s_free(buffer);
        s_log("s_file_read: fread error for file '%s'", filename);
        return NULL;
    }
    buffer[size] = '\0';

    s_log("s_file_read: Read %ld bytes from '%s'", size, filename);
    return buffer;
}

int s_file_write(const char* filename, const char* data) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        s_log("s_file_write: Failed to open file '%s' for writing", filename);
        return 0;
    }
    size_t len = strlen(data);
    size_t written = fwrite(data, 1, len, file);
    fclose(file);
    if (written != len) {
        s_log("s_file_write: fwrite error for file '%s'", filename);
        return 0;
    }
    s_log("s_file_write: Wrote %zu bytes to '%s'", len, filename);
    return 1;
}
