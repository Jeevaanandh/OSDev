[ORG 0x7C00]
[BITS 16]

mov ax, 0x0000
mov ds, ax
mov ss, ax
mov sp, 0x7C00

read:
mov ax, 0x1000
mov es, ax   ; Code segment starts from 1000H
mov bx, 0x0000

mov ah, 0x02 ; READ SECTORS (BIOS FUNCTION)
mov al, 4    ; Read 4 sectors
mov ch, 0    ; cylinder=0
mov cl, 2    ; sector=2  ie. Read from the second sector. Since, the kernel code is availabe from the second sector

mov dh, 0    ; Head=0
mov dl, 0x80 ; Drive

int 0x13     ; This is the BIOS interrupt for disk reading

jmp 0x1000:0x0000  ; Jump to the kernel Code

times 510 - ($ - $$) db 0
dw 0xAA55
