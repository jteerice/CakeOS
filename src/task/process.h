#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "task.h"
#include "config.h"

struct process {

	uint16_t id;
	char filename[CAKEOS_MAX_PATH];
	// Main process task
	struct task* task;
	// Malloc allocations of the process
	void* allocations[CAKEOS_MAX_PROGRAM_ALLOCATIONS];
	// Physical pointer to process mem
	void* ptr;
	// Physical pointer to stack mem
	void* stack;
	// Size of the data pointed to by ptr
	uint32_t size;

};

#endif
