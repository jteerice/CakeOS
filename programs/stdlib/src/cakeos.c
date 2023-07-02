#include "cakeos.h"

int cakeos_getkeyblock() {

	int val = 0;
	do {
		val = cakeos_getkey();
	} while (val == 0);

	return val;
}

void cakeos_terminal_readline(char* out, int max, bool output_while_typing) {

	int i = 0;
	for (i = 0; i < max - 1; i++) {
		char key = cakeos_getkeyblock();
		// Check for enter key
		if (key == 13) {
			break;
		}

		if (output_while_typing) {
			cakeos_putchar(key);
		}

		// Backspace
		if (key == 0x08 && i >= 1) {
			out[i - 1] = 0x00;
			i -= 2;
			continue;
		}

		out[i] = key;
	}

	out[i] = 0x00;
}
