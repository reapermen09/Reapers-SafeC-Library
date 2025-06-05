#ifndef SAFEC_CASTING_H
#define SAFEC_CASTING_H

int s_to_int(const char* str, int* out);

int s_to_float(const char* str, float* out);

int s_to_double(const char* str, double* out);

char* s_from_int(int value);

char* s_from_float(float value);

char* s_from_double(double value);

int s_to_bool(const char* str);

#endif