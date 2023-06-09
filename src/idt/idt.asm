section .asm

extern int21h_handler
extern no_interrupt_handler
extern isr80h_handler
extern interrupt_handler

global idt_load
global no_interrupt
global enable_interrupts
global disable_interrupts
global isr80h_wrapper
global interrupt_pointer_table

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

no_interrupt:
	cli
	pushad
	call no_interrupt_handler
	popad
	sti
	iret	

%macro interrupt 1
	global int%1
	int%1:
		pushad
		push esp
		push dword %1
		call interrupt_handler
		add esp, 8
		popad
		iret
%endmacro

%assign i 0
%rep 512
	interrupt i
%assign i i+1
%endrep

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

section .data
; Store the return value from int 80
res: dd 0


%macro interrupt_array_entry 1
	dd int%1
%endmacro

interrupt_pointer_table:
%assign i 0
%rep 512
	interrupt_array_entry i
%assign i i+1
%endrep


