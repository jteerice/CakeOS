#ifndef DISK_H
#define DISK_H

#include "fs/file.h"

typedef unsigned int CAKEOS_DISK_TYPE;

// Represents a physical hard disk
#define CAKEOS_DISK_TYPE_REAL 0

struct disk {

	CAKEOS_DISK_TYPE type;
	int sector_size;

	int id;

	struct filesystem* filesystem;

	// Private data of the filesystem
	void* fs_data;

};

void disk_search_and_init();
struct disk* disk_get(int index);
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf);

#endif
