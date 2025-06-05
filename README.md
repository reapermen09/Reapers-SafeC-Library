# Reaper's SafeC Library
SafeC is a lightweight C library released with the MIT License that provides safe, dynamic alternatives for common tasks in C such as string manipulation, user input, etc; and prevents Buffer Overflows.

⚠️ Although this library works in C++, Safe C is primarly targeted for C.

NOTE: USE `#define SAFEC_DEBUG` for logging and make sure it is above `#include "safec.h"` and use the `s_log(); function. COMPLETY OPTIONAL!

Example:
```
#include "safec.h"
// stdio include not needed because safec.h includes it

int main()
{
    s_print("Enter your name: ");
    char* name = s_input();
    if (name)
    {
        s_print_ln("Hello, %s!", name);
        free(name);
    }
    else
    {
        s_print_ln("Failed to read input.");
    }
    return 0;
}
```

Functions which are included on this library are:
```
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
```
