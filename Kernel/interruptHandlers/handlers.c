#include<stdint.h>
#include "../setup/pic.h"
#include "../std/stdFunctions.h"

//THIS IS A GENERAL HANDLER FOR INTERRUPTS
void int_handler(){
    printk("Interrupt has occured\n");

    outb(0x20, 0x20);
    outb(0xA0, 0x20);
}


//THIS IS THe HANDLER FOR KEYBOARD INTERRUPT
void keyboard_handler(){
    uint8_t scancode = inb(0x60);   //READING THE SCAN CODE FROM THE DATA PORT OF THE KEYBOARD CONTROLLER

    if(scancode<0x80){
        printk("Key Pressed\n");
    }
    

    //SENDING THE EOI (END OF INTERRUPT) COMMAND TO THE PIC'S

    //0x20 IS THE CODE TO SIGNAL EOI
    outb(0x20, 0x20);
    outb(0xA0, 0x20);
}