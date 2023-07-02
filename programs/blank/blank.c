#include "cakeos.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv) {

	print("Hello World!\n");
	print(itoa(1234));	

	putchar('Z');
		
	void* ptr = malloc(512);
	free(ptr);

	while (1) {
		if (getkey() != 0) {
			print("Key pressed!\n");
		}
	}

	return 0;
}
