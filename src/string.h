#ifndef STRING_H
#define STRING_H

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

#endif
