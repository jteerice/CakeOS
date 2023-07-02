#ifndef CAKEOS_H
#define CAKEOS_H

#include <stddef.h>

void print(const char* message);
int getkey();
void* cakeos_malloc(size_t size);
void cakeos_free(void* ptr);
void cakeos_putchar(char c);

#endif
