#include<stdint.h>

#define IDT_SIZE 256

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


//THE IDT IS CURRENTLY EMPTY. NOTHING WAS INSERTED.
void createIDT(){

    idtr.size= sizeof(idt)-1;
    idtr.offset= (uint32_t)&idt;

    //This is inline assembly. It is basically lidt [idtr]
    asm volatile("lidt %0" : : "m"(idtr));

    return;

}
