#ifndef CAKEOS_H
#define CAKEOS_H

#include <stddef.h>
#include <stdbool.h>

struct command_argument {

	char argument[512];
	struct command_argument* next;

};

void print(const char* message);
int cakeos_getkey();
void* cakeos_malloc(size_t size);
void cakeos_free(void* ptr);
void cakeos_putchar(char c);
int cakeos_getkeyblock();
void cakeos_terminal_readline(char* out, int max, bool output_while_typing);
void cakeos_process_load_start(const char* filename);
struct command_argument* cakeos_parse_command(const char* command, int max);

#endif
