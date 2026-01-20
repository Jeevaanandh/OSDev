[ORG 0x10000]
[BITS 32]


mov esi, message
mov edi, 0xB8000

print:
	lodsb
	cmp al, 0
	je loop
	mov ah, 0x0F
	mov [edi], ax
	inc edi
	inc edi
	jmp print

loop: jmp loop

message db "Hello From the Kernel!!!", 0



