[ORG 0x0000]
[BITS 16]

mov ax, 0x1000
mov ds, ax
mov si, message

print:
	lodsb
	cmp al, 0
	je loop
	mov ah, 0x0E
	mov bh, 0x00
	mov bl, 0x08
	int 0x10
	jmp print

loop: jmp loop

message db "Hello From the Kernel!!!", 0

times 510-($-$$) db 0


