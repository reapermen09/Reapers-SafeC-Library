#include "safec.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

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

    char* buffer = (char*)s_malloc((size_t)size + 1);
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

int s_file_append(const char* filename, const char* data) {
    FILE* file = fopen(filename, "ab");
    if (!file) {
        s_log("s_file_append: Failed to open file '%s' for appending", filename);
        return 0;
    }
    size_t len = strlen(data);
    size_t written = fwrite(data, 1, len, file);
    fclose(file);
    if (written != len) {
        s_log("s_file_append: fwrite error for file '%s'", filename);
        return 0;
    }
    s_log("s_file_append: Appended %zu bytes to '%s'", len, filename);
    return 1;
}

int s_file_exists(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}
#ifdef _WIN32

int s_path_exists(const char* path) {
    DWORD attrib = GetFileAttributesA(path);
    if (attrib == INVALID_FILE_ATTRIBUTES) {
        return 0;
    }
    return 1;
}

#else

#include <sys/stat.h>

int s_path_exists(const char* path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0) ? 1 : 0;
}

#endif

int s_file_contains(const char* filename, const char* substring) {
    if (!filename || !substring) return -1;

    char* content = s_file_read(filename);
    if (!content) return -1;

    int result = (strstr(content, substring) != NULL) ? 1 : 0;

    s_free(content);
    return result;
}