#include "pparser.h"
#include "kernel.h"
#include "string/string.h"
#include "memory/heap/kheap.h"
#include "memory/memory.h"

static int path_valid_format(const char* filename) {

	int len = strnlen(filename, CAKEOS_MAX_PATH);

	return (len >= 3 && isdigit(filename[o]) && memcmp((void*)&filename[1], ":/", 2) ==0);
}
