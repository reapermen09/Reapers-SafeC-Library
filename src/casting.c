#ifdef _WIN32
#define strcasecmp _stricmp
#else
#include <strings.h>
#endif

#include "casting.h"
#include "safec.h"
#include "string.h"
#include <stdint.h>

int s_to_int(const char* str, int* out) {
    if (!str || !out) return 0;
    char* end;
    long val = strtol(str, &end, 10);
    if (*end != '\0') return 0;
    *out = (int)val;
    return 1;
}

int s_to_float(const char* str, float* out) {
    if (!str || !out) return 0;
    char* end;
    float val = strtof(str, &end);
    if (*end != '\0') return 0;
    *out = val;
    return 1;
}

int s_to_double(const char* str, double* out) {
    if (!str || !out) return 0;
    char* end;
    double val = strtod(str, &end);
    if (*end != '\0') return 0;
    *out = val;
    return 1;
}

char* s_from_int(int value) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", value);
    return s_strdup(buffer);
}

char* s_from_float(float value) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%.2f", value);
    return s_strdup(buffer);
}

char* s_from_double(double value) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%.3f", value);
    return s_strdup(buffer);
}

int s_to_bool(const char* str) {
    if (!str) return -1;

    if (strcasecmp(str, "true") == 0 || strcmp(str, "1") == 0 || strcasecmp(str, "yes") == 0)
        return 1;

    if (strcasecmp(str, "false") == 0 || strcmp(str, "0") == 0 || strcasecmp(str, "no") == 0)
        return 0;

    return -1;
}
