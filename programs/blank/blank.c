#include "cakeos.h"
#include "stdlib.h"

int main(int argc, char** argv) {

	print("Hello World!\n");
	print(itoa(1234));	
		
	void* ptr = malloc(512);
	free(ptr);

	while (1) {
		if (getkey() != 0) {
			print("Key pressed!\n");
		}
	}

	return 0;
}
