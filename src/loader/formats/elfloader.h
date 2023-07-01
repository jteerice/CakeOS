#ifndef ELFLOADER_H
#define ELFLOADER_H

#include <stdint.h>
#include <stddef.h>

#include "elf.h"
#include "config.h"

struct elf_file {

	char filename[CAKEOS_MAX_PATH];
	int in_memory_size;

	// The physical mem addr that this elf file is loaded to
	void* elf_memory;

	// The virtual base addr of this binary
	void* virtual_base_address;
	
	// End virtual address
	void* virtual_end_address;

	// Physical base address
	void* physical_base_address;

	// Physical end address
	void* physical_end_address;

};

int elf_load(const char* filename, struct elf_file** file_out);
void elf_close(struct elf_file* file);
void* elf_virtual_base(struct elf_file* file);
void* elf_virtual_end(struct elf_file* file);
void* elf_phys_base(struct elf_file* file);
void* elf_phys_end(struct elf_file* file);

#endif
