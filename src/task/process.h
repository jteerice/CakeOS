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

	struct keyboard_buffer {

		char buffer[CAKEOS_KEYBOARD_BUFFER_SIZE];
		int tail;
		int head;

	} keyboard;

};

int process_load(const char* filename, struct process** process);
int process_load_for_slot(const char* filename, struct process** process, int process_slot);
struct process* process_current();
struct process* process_get(int process_id);
int process_load_switch(const char* filename, struct process** process);
int process_switch(struct process* process);

#endif
