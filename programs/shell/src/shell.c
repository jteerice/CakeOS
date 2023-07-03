#include "shell.h"
#include "stdio.h"
#include "stdlib.h"
#include "cakeos.h"


int main(int argc, char** argv) {

	print("CakeOS v1.0.0\n");
	while (1) {
		print("> ");
		char buf[1024];
		cakeos_terminal_readline(buf, sizeof(buf), true);
		print("\n");
		cakeos_system_run(buf);
		print("\n");
	}

	return 0;
}
