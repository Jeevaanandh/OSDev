[BITS 32]
global start
extern kernel_entry

start:
	call kernel_entry  ; jump into C
    hlt


