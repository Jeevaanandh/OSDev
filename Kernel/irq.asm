[BITS 32]

extern int_handler
extern keyboard_handler

global general_irq
global keyboard_irq

general_irq:
    pusha
    call int_handler
    popa

    iret


;THIS IS THE ISR FOR IRQ1 (KEYBOARD INTERRUPT)
keyboard_irq:
    pusha
    call keyboard_handler
    popa

    iret




