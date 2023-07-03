[BITS 32]

global _start
extern c_start
extern cakeos_exit

section .asm

_start:
	call c_start
	call cakeos_exit
	ret
