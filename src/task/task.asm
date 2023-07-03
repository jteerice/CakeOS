[BITS 32]

section .asm

global restore_general_purpose_registers
global task_return
global user_registers

task_return:
	mov ebp, esp
	; Push data segment
	; Push stack address
	; Push the flags
	; Push the code segment
	; Push ip

	mov ebx, [ebp+4]
	; Push the data/stack selector
	push dword [ebx+44]
	; Push stack pointer
	push dword [ebx+40]
	; Push the flags
	pushf
	pop eax
	or eax, 0x200
	push eax
	; Push code segment
	push dword [ebx+32]
	; Push the ip to execute
	push dword [ebx+28]
	; Setup segment registers
	mov ax, [ebx+44]
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	push dword [ebp+4]
	call restore_general_purpose_registers
	add esp, 4	

	; Leave kernal space and execute in user space
	iretd

; void restore_general_purpose_registers(struct registers* regs);
restore_general_purpose_registers:
	push ebp
	mov ebp, esp
	mov ebx, [ebp+8]
	mov edi, [ebx]
	mov esi, [ebx+4]
	mov ebp, [ebx+8]
	mov edx, [ebx+16]
	mov ecx, [ebx+20]
	mov eax, [ebx+24]
	mov ebx, [ebx+12]
	add esp, 4
	ret

user_registers:
	mov ax, 0x23
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	ret
