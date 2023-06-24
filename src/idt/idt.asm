section .asm

extern int21h_handler
extern no_interrupt_handler
extern isr80h_handler

global idt_load
global int21h
global no_interrupt
global enable_interrupts
global disable_interrupts
global isr80h_wrapper

section .data
; Store the return value from int 80
res: dd 0

enable_interrupts:
	sti
	ret

disable_interrupts:
	cli
	ret

idt_load:
	push ebp
	mov ebp, esp
	mov ebx, [ebp+8]
	lidt [ebx]
	pop ebp
	ret	

int21h:
	cli
	pushad
	call int21h_handler
	popad
	sti
	iret	

no_interrupt:
	cli
	pushad
	call no_interrupt_handler
	popad
	sti
	iret	

isr80h_wrapper:
	cli
	; Push general purpose registers	
	pushad
	
	; Push the stack pointer to point to the interrupt frame
	push esp

	; Push command code and call int 80 handler
	push eax
	call isr80h_handler
	mov dword [res], eax
	add esp, 8
	
	; Restore registers for user space
	popad
	mov eax, [res]
	iretd
