# Reaper's SafeC Library
SafeC is a cross-platform lightweight C library released with the MIT License that provides safe, dynamic alternatives for common tasks in C such as string manipulation, user input, etc; and prevents Buffer Overflows.

⚠️ Although this library works in C++, Safe C is primarly targeted for C.

NOTE: USE `#define SAFEC_DEBUG` for logging and make sure it is above `#include "safec.h"` and use the `s_log(); function. COMPLETY OPTIONAL!

Also, on visual studio... you must add the files to do project as existing files.

NOTE: ON OLDER VERSIONS THAN v0.4 YOU MUST USE "_CRT_SECURE_NO_WARNINGS"

Properly coded example:
```
#include "safec.h"
#include "io.h"

int main()
{
    s_alloc_init();
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

What your code may look like without Safe C:

```
#include <stdio.h>
#include <string.h>

int main()
{
    char name[100];

    printf("Enter your name: ");
    if (fgets(name, sizeof(name), stdin))
    {
        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n')
            name[len - 1] = '\0';
        printf("Hello, %s!\n", name);
    }
    else
    {
        printf("Failed to read input.\n");
    }

    return 0;
}

```

CONS w/o Safe C: FIXED-SIZED, MORE BOILER PLATE

BENEFITS of Safe C: DYNAMICALLY MANAGED BUFFERS, LESS BOILER PLATE, ETC.

Includes:
```
#include "safec.h"

#include "file.h"

#include "io.h"

#include "string.h"

#include "casting.h"
```

Functions which are included on this library are:
```
int s_to_int(const char* str, int* out);

int s_to_float(const char* str, float* out);

int s_to_double(const char* str, double* out);

char* s_from_int(int value);

char* s_from_float(float value);

char* s_from_double(double value);

int s_to_bool(const char* str);

char* s_file_read(const char* filename);

int s_file_write(const char* filename, const char* data);

int s_file_append(const char* filename, const char* data);

int s_file_exists(const char* filename);

char* s_input(void);

void s_print(const char* fmt, ...);

void s_print_ln(const char* fmt, ...);

char* s_strdup(const char* str);

char** s_strsplit(const char* str, char delim, size_t* out_count);

void s_strsplit_free(char** arr, size_t count);

char* s_strcat(char* dest, size_t* dest_size, const char* src);

int s_strcmp(const char* s1, const char* s2);

char* s_strcpy(char* dest, size_t dest_size, const char* src);

char* s_substr(const char* str, size_t start, size_t length);

char* s_strtrim(const char* str);

char* s_to_lower(const char* str);

char* s_strrev(const char* str);

int s_stricmp_case_insensitive(const char* s1, const char* s2);
```

# MIT LICENSE

* You may use this freely in any project.

* You may not claim ownership of Safe C by Reapermen
