#include "stdio.h"
#include "cakeos.h"

int putchar(int c) {

	cakeos_putchar((char)c);
	return 0;
}
