#ifndef STRING_H
#define STRING_H
#include <stdbool.h>

int strlen(const char* str);
char* strcpy(char* dest, const char* src);
bool isdigit(char c);
int tonumericdigit(char c);
int strnlen(const char* str, int max);

#endif
