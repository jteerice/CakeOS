ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

jmp short start
nop

; FAT16 Header
OEMIdentifier 		db 'CAKEOS  ' ; 8 bytes padded with spaces
BytesPerSector 		dw 0x200
SectorsPerCluster 	db 0x80
ReservedSectors 	dw 200 ; 200 reserved sectors to store the kernel
FATCopies 		db 0x02
RootDirEntries 		dw 0x40
NumSectors 		dw 0x00
MediaType 		db 0xF8
SectorsPerFat 		dw 0x100
SectorsPerTrack 	dw 0x20
NumberOfHeads 		dw 0x40
HiddenSectors 		dd 0x00
SectorsBig 		dd 0x773594

; Extended BPB (Dos 4.0)
DriverNumber 		db 0x80
WinNTBit 		db 0x00
Signature 		db 0x29
VolumeID 		dd 0xD105
VolumeIDString		db 'CAKEOS BOOT' ; 11 byte limit
SystemIDString		db 'FAT16   ' ; 8 bytes padded with spaces

start:
	jmp 0:step2

step2:
	cli ; Clear Interrupts
	mov ax, 0x00 
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7c00
	sti ; Enables Interrupts

.load_protected:
	cli
	lgdt[gdt_descriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEG:load32

; Global Descriptor Table
gdt_start:
gdt_null:
	dd 0x0
	dd 0x0

; offset 0x8
gdt_code: ; CS should point here
	dw 0xffff ; Segment limit first 0-15 bits
	dw 0 ; Base first 0-15 bits
	db 0 ; Base 16-23 bits
	db 0x9a ; Access byte
	db 11001111b ; High 4 bit flags and the low 4 bit flags
	db 0 ; Base 24-31 bits

; offset 0x10
gdt_data: ; DS, SS, ES, FS, GS
	dw 0xffff
	dw 0
	db 0
	db 0x92
	db 11001111b
	db 0

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start-1
	dd gdt_start

[BITS 32]
load32:
	mov eax, 1
	mov ecx, 100
	mov edi, 0x0100000
	call ata_lba_read
	jmp CODE_SEG:0x0100000

ata_lba_read:
	mov ebx, eax ; Backup the lba
	; Send the highest 8 bits of the lba to hard disk controller
	shr eax, 24
	or eax, 0xE0 ; Select the master drive
	mov dx, 0x1F6
	out dx, al
	; Finished sending the highest 8 bits of the lba

	; Send the total sectors to read
	mov eax, ecx
	mov dx, 0x1F2
	out dx, al
	; Finished sending the total sectors to read

	; Send more bits of the lba
	mov eax, ebx ; Restore the backup lba
	mov dx, 0x1F3
	out dx, al
	; Finished sending more bits of the lba

	; Send more bits of the lba
	mov dx, 0x1F4
	mov eax, ebx ; Restore the backup lba
	shr eax, 8
	out dx, al
	; Finished sending more bits of the lba

	; Send upper 16 bits of the lba
	mov dx, 0x1F5
	mov eax, ebx ; Restore backup lba
	shr eax, 16
	out dx, al
	; Finished sending upper 16 bits of the lba

	mov dx, 0x1f7
	mov al, 0x20
	out dx, al

; Read all sectors into memory
.next_sector:
	push ecx	

; Check if we need to read	
.try_again:
	mov dx, 0x1f7
	in al, dx
	test al, 8
	jz .try_again

; Need to read 256 words at a time
	mov ecx, 256
	mov dx, 0x1F0
	rep insw
	pop ecx
	loop .next_sector
	; End of reading sectors into memory
	ret
	
times 510- ($ - $$) db 0
dw 0xAA55
