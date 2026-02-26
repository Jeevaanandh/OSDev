#include<stdint.h>
#include "pic.h"
#include "../InlineAssembly/inline.h"


#define MASTER_CMD 0x20
#define MASTER_DATA 0x21
#define SLAVE_CMD 0xA0
#define SLAVE_DATA 0xA1

//THE REMAPPING HAS TO HAPPEN IN STEPS. ICW REPRESENTS THE STEPS

/*
ICW1 ----- Is used to let the PIC knwo that we are initializing it.

ICW2 ----- Is to let the PIC know the offset. ie. IRQ0 of Master PIC starts from 0x20. This is the main Re-mapping

ICW3 ----- Is to let the the PIC's know how they are connected to eachother

ICW4 ----- Is to let the two PIC's know which CPU they are in.

*/



#define ICW1 0x10   // THIS IS TO TELL THE PIC THAT INITILAIZATION IS BEING DONE
#define ICW3_MASTER 0x04   // THIS IS TO TELL THAT THE MASTER PIC THAT THE SLAVE PIC IS CONNECTED TO THE MASTER PIC AT IRQ2
#define ICW3_SLAVE 0x02  // THIS IS TO TELL THE SLAVE PIC IT IS CONNECTED TO IRQ2 OF THE MASTER PIC

#define ICW1_ICW4 0x01    // THIS IS TO LET THE PIC KNOW THAT AFTER ICW2 AND ICW3, ICW4 WILL ALSO BE SENT. THIS IS USED TO SET A BIT IN ICW1

#define ICW4 0x01         // 8086 MODE



//EACH PIC HAS ITS OWN DATA AND COMMAND PORT. 
/*
    outb is used to write data into the port

    inb is used to read from the port.

*/ 







void remapPIC(int offset1, int offset2){
    //ICW1
    outb(MASTER_CMD, ICW1|ICW1_ICW4);
    outb(SLAVE_CMD, ICW1|ICW1_ICW4);

    //ICW2
    outb(MASTER_DATA, offset1);
    outb(SLAVE_DATA, offset2);

    //ICW3
    outb(MASTER_DATA, ICW3_MASTER);
    outb(SLAVE_DATA, ICW3_SLAVE);

    //ICW4
    outb(MASTER_DATA, ICW4);
    outb(SLAVE_DATA, ICW4);

    //DISABLING IRQ0. ie. TIMER INTERRUPT
    uint8_t mask = inb(0x21);
    mask |= 1 << 0;        // Set bit 0
    outb(0x21, mask);

    sti();


}