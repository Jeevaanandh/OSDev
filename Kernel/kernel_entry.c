#include "setup/idt.h"
#include "setup/pic.h"
#include "std/stdFunctions.h"
#include "drivers/disk.h"
#include "sched/task_struct.h"
#include "TestPrograms.h"




void kernel_entry() {
    //CREATING THE IDT
    createIDT();

    //CLEARING THE SCREEN
    clear_screen();
    createTask(&Task1);
    createTask(&Task2);

    printk("IDT has been created!!!\n");
    printk("Hello from C kernel!\n");
    remapPIC(0x20, 0x28);
    printk("PIC Has been re-mapped!!!\n");

    char buffer[512];


    printk("Task has been created!!!\n");


    /*
    get_sector(0, buffer);

    printk("Disk Read: \n");
    for(int i=0; i<512; i++){
        printk("%x ", buffer[i]);
    }

   

    printk("\n");
    printk("%x ", (unsigned char)buffer[510]);
    printk("%x ", (unsigned char)buffer[511]);

    */



    
    while (1);
}
