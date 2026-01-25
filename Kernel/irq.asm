[BITS 32]

extern int_handler
extern keyboard_handler

global general_irq
global keyboard_irq


;THIS IS THE GENERAL ISR FOR OTHER INTERRUPTS
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




