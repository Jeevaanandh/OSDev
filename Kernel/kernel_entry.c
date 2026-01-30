#include "setup/idt.h"
#include "setup/pic.h"
#include "std/stdFunctions.h"



void kernel_entry() {
    //CREATING THE IDT
    createIDT();

    //CLEARING THE SCREEN
    clear_screen();
    printk("IDT has been created!!!\n");
    printk("Hello from C kernel!\nHello again!!! %c\n",'a');
    printk("Second Hello\n");

    remapPIC(0x20, 0x28);
    printk("PIC Has been re-mapped!!!\n");

    
    
    while (1);
}
