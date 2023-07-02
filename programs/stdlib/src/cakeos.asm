[BITS 32]

section .asm

global print:function
global cakeos_getkey:function
global cakeos_malloc:function
global cakeos_free:function
global cakeos_putchar:function

; void print(const char* message)
print:
	push ebp
	mov ebp, esp
	push dword[ebp+8]
	mov eax, 1
	int 0x80
	add esp, 4
	pop ebp
	ret

cakeos_getkey:
	push ebp
	mov ebp, esp
	mov eax, 2
	int 0x80
	pop ebp
	ret

cakeos_putchar:
	push ebp
	mov ebp, esp
	mov eax, 3
	push dword [ebp+8]
	int 0x80
	add esp, 4
	pop ebp
	ret

; void* cakeos_malloc(size_t size)
cakeos_malloc:
	push ebp
	mov ebp, esp
	mov eax, 4
	push dword[ebp+8]
	int 0x80
	add esp, 4
	pop ebp
	ret

cakeos_free:
	push ebp
	mov ebp, esp
	mov eax, 5
	push dword[ebp+8]
	int 0x80
	add esp, 4
	pop ebp
	ret
