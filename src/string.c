#include "safec.h"
#include "string.h"

char* s_strdup(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* dup = (char*)s_malloc(len + 1);
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

    char** result = (char**)s_malloc(sizeof(char*) * count);
    if (!result) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    size_t idx = 0;
    const char* start = str;
    for (const char* p = str; ; p++) {
        if (*p == delim || *p == '\0') {
            size_t len = p - start;
            char* token = (char*)s_malloc(len + 1);
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
        char* new_buf = (char*)s_malloc(new_size);
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
        char* temp = (char*)s_realloc(dest, new_size);
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
        char* empty = (char*)s_malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }
    if (start + length > str_len) {
        length = str_len - start;
    }
    char* sub = (char*)s_malloc(length + 1);
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
        char* empty = (char*)s_malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }

    const char* end = str + strlen(str);
    while (end > start && isspace((unsigned char)*(end - 1))) end--;

    size_t len = end - start;
    char* trimmed = (char*)s_malloc(len + 1);
    if (!trimmed) return NULL;
    memcpy(trimmed, start, len);
    trimmed[len] = '\0';
    return trimmed;
}

char* s_to_lower(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* lower = (char*)s_malloc(len + 1);
    if (!lower) return NULL;
    for (size_t i = 0; i < len; i++) {
        lower[i] = (char)tolower((unsigned char)str[i]);
    }
    lower[len] = '\0';
    return lower;
}

int s_starts_with(const char* str, const char* prefix) {
    if (!str || !prefix) return 0;
    size_t len = strlen(prefix);
    return strncmp(str, prefix, len) == 0;
}

int s_ends_with(const char* str, const char* suffix) {
    if (!str || !suffix) return 0;
    size_t str_len = strlen(str), suffix_len = strlen(suffix);
    if (suffix_len > str_len) return 0;
    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

char* s_strrev(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* rev = (char*)s_malloc(len + 1);
    if (!rev) return NULL;
    for (size_t i = 0; i < len; i++) {
        rev[i] = str[len - i - 1];
    }
    rev[len] = '\0';
    return rev;
}

int s_stricmp_case_insensitive(const char* s1, const char* s2) {
    if (!s1 && !s2) return 0;
    if (!s1) return -1;
    if (!s2) return 1;

    while (*s1 && *s2) {
        int diff = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        if (diff != 0) return diff;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}