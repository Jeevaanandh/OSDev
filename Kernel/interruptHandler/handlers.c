#include<stdint.h>
#include "../InlineAssembly/inline.h"
#include "../std/stdFunctions.h"
#include "../drivers/keyboard.h"

//THIS IS A GENERAL HANDLER FOR INTERRUPTS
void int_handler(){
    printk("Interrupt has occured\n");

    outb(0x20, 0x20);
    outb(0xA0, 0x20);
}


//THIS IS THe HANDLER FOR KEYBOARD INTERRUPT

/*

    For a proper use, create a keyboard driver ie. Decode scan codes properly to make a working keyboard.

    Call the keyboard_driver function from the keyboard_handler.


*/





// This is the function we jump to in irq.asm upon Keyboard Interrupt.
void keyboard_handler(){
    keyboard();
}