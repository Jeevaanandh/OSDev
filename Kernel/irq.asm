[BITS 32]

extern int_handler
extern keyboard_handler
extern timer_handler
extern schedule

global general_irq
global keyboard_irq
global timer_irq


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


timer_irq:
    pusha                ; save registers

    mov eax, esp         ; pass current esp to timer_handler
    push eax
    call timer_handler

    pop ebx              ; Removing the EAX values we added to the stack and storing it in EBX.

    ;When we call a C function from assembly, it return value is placed in EAX.
    mov esp, eax         ; timer_handler calls scheduler, which returns NEW esp in eax

    ;So, the registers are restored.
    popa                 ; restore registers from NEW task stack

    iret






