ORG 0x7C00
[BITS 16]





jmp start
nop

oem                 db "MSWIN4.1"

bytesPerSector      dw 512
sectorsPerCluster   db 4
reservedSectors     dw 1
numberOfFats        db 2
rootEntryCount      dw 512
totalSectors16      dw 40960
mediaDescriptor     db 0xF8
sectorsPerFAT       dw 40
sectorsPerTrack     dw 63
numberOfHeads       dw 16
hiddenSectors       dd 0
totalSectors32      dd 0



GDT_Start:
	null_descriptor:
		dd 0
		dd 0

	code_descriptor:
		dw 0xffff
		dw 0
		db 0
		db 10011010b
		db 11001111b
		db 0

	data_descriptor:
		dw 0xffff
		dw 0
		db 0
		db 10010010b
		db 11001111b
		db 0

GDT_End:

GDT_Descriptor:
	dw GDT_End - GDT_Start -1
	dd GDT_Start

CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start


start:
lgdt [GDT_Descriptor]

; STILL IN REAL MODE

read_from_disk:
	mov ax, 0x1000
	mov es, ax
	mov bx, 0x0000

	mov ah, 0x02
	mov al, 20     ;no. of sectors to read
	mov ch, 0
	mov cl, 2
	mov dh, 0
	mov dl, 0x80

	int 0x13

; KERNEL CODE LOADED TO MEMORY at 10000.  NOT 1000 Since it is stored at ES:BX= 0x1000 * 0x10 + 0x0000

call SET_A20

cli

mov eax, cr0
or eax, 1
mov cr0, eax

jmp dword CODE_SEG:start_protected_mode			; dword ensures 16-bit:32-bit jump happens. Since start_protected_mode is defined inside the 32 bit region


[bits 32]

start_protected_mode:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov esp, 0x9FC00      ; This is stack pointer

	jmp 0x00010000 ; Jump to the kernal code. 32 bit addressing


loop: jmp loop

SET_A20:
	in  al, 0x92
    or  al, 00000010b   ; set bit 1.  bit1 is A20
    out 0x92, al
    ret

times 510- ($-$$) db 0

dw 0xAA55