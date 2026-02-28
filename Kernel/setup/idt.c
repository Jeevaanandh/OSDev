#include<stdint.h>

#define IDT_SIZE 256

//ASSEMBLY FUNCTIONS. THEY ARE THE IRQ'S
extern void general_irq();
extern void keyboard_irq();
extern void timer_irq();



struct IDT_Entry{
    uint16_t offset1;
    uint16_t segment_selector;
    uint8_t res;
    uint8_t type_attr;
    uint16_t offset2;

} __attribute__((packed));

struct IDT_Descriptor{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));


//THESE ARE SUPPOSED TO BE GLOBAL VARIABLES. IF NOT, THE LIVE IN THE STACK OF THE FUNCTION AND ARE GONE ONCE THE FUNCTION RETURNS.

//Loading the idt into the memory
struct IDT_Entry idt[256];

//loding the IDT Descriptor into the memory
struct IDT_Descriptor idtr;



void addIDT_entries(){
    for(int i=0; i<256; i++){
        uint32_t offset;

        if (i==32) {
            offset= (uint32_t)&timer_irq;
        }

        //i=33 is IRQ1 (KEYBOARD INTERRUPT)
        else if(i==33){
            offset= (uint32_t)&keyboard_irq;

        }

        else{
            offset= (uint32_t)&general_irq;
        }
        

        idt[i].offset1= offset & 0xFFFF;
        idt[i].segment_selector= 0x08;
        idt[i].res=0;

        

        
        idt[i].type_attr= 0b10001110;
        
        

        idt[i].offset2= (offset>>16) & 0xFFFF;
        
        
    }

}


void createIDT(){

    addIDT_entries();

    idtr.size= sizeof(idt)-1;
    idtr.offset= (uint32_t)&idt;

    //This is inline assembly. It is basically lidt [idtr]
    asm volatile("lidt %0" : : "m"(idtr));

    

    return;

}



