#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include <stdint.h>
#include <stddef.h>
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "string/string.h"
#include "disk/streamer.h"
#include "fs/file.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char color) {

	return (color << 8) | c;
}

void terminal_putchar(int x, int y, char c, char color) {

	video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, color);

}

void terminal_writechar(char c, char color) {

	if (c == '\n') {
		terminal_row++;
		terminal_col = 0;
	} else {
		terminal_putchar(terminal_col, terminal_row, c, color);
		terminal_col++;

		if (terminal_col >= VGA_WIDTH) {
			terminal_col = 0;
			terminal_row++;
		}
	}

}


void terminal_initialize() {

	video_mem = (uint16_t*)(0xB8000);
	terminal_row = 0;
	terminal_col = 0;

	for (int y = 0; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			terminal_putchar(x, y, ' ', 0);
		}
	}

}

void print(const char* str) {

	size_t len = strlen(str);

	for (int i = 0; i < len; i++) {
		terminal_writechar(str[i], 15);
	}

}

static struct paging_4gb_chunk* kernel_chunk = 0;
void kernel_main() {

	terminal_initialize();
	print("Hello World!\n"); 

	// Initialize heap
	kheap_init();

	// Initialize filesystems
	fs_init();

	// Search and initialize disk
	disk_search_and_init();

	// Initialize Interrupt Descriptor Table
	idt_init();

	// Setup paging
	kernel_chunk = paging_new_4gb(PAGING_IS_WRITABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

	// Switch to kernel paging chunk
	paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

	// Enable paging
	enable_paging();

	// Enable system interrupts
	enable_interrupts();
	
	int fd = fopen("0:/hello.txt", "r");
	if (fd) {
		print("We opened hello.txt\n");
		char buf[14];
		fread(buf, 13, 1, fd);
		buf[13] = 0x00;
		print(buf);
	}
	while (1) {
	}
}
