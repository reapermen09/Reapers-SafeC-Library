#ifndef FILE_H
#define FILE_H

char* s_file_read(const char* filename);

int s_file_write(const char* filename, const char* data);

int s_file_append(const char* filename, const char* data);

int s_file_exists(const char* filename);

#ifdef _WIN32
int s_path_exists(const char* path);
#else
#include <sys/stat.h>
int s_path_exists(const char* path);
#endif

int s_file_contains(const char* filename, const char* substring);

#endif
