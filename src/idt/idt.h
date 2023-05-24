#ifndef IDT_H
#define IDT_H

#include <stdint.h>
struct idt_desc {

	uint16_t offset_1; // Offset bits 0 - 15
	uint16_t selector; // Selector thats in our GDT
	uint8_t zero;     // Nothing
	uint8_t type_attr;// Descriptor type and attributes
	uint16_t offset_2; // Offset bits 16 - 31
			   
}__attribute__((packed));

struct idtr_desc {

	uint16_t limit; // Size of descriptor table
	uint32_t base;  // Base address of descriptor table

}__attribute__((packed));

void idt_init();

#endif
