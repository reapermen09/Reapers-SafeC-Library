# SafeC Library
SafeC is a lightweight C library that provides safe, dynamic alternatives for common tasks in C — such as string manipulation, user input, and formatted printing — without risking buffer overflows or unsafe memory handling.

⚠️ Although this library works in C++, it's primarily designed for C projects and is best suited for C developers who want safer and more flexible handling of strings and I/O.

Functions which are included on this library are:
```char* s_input(void);

void s_print(const char* fmt, ...);

void s_print_ln(const char* fmt, ...);

char* s_strdup(const char* str);

char* s_strcat(char* dest, size_t* dest_size, const char* src);

int s_strcmp(const char* s1, const char* s2);

char* s_strcpy(char* dest, size_t dest_size, const char* src);

char* s_substr(const char* str, size_t start, size_t length);

char* s_strtrim(const char* str);

char** s_strsplit(const char* str, char delim, size_t* out_count);

void s_strsplit_free(char** arr, size_t count);```
