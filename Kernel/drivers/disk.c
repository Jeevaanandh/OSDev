#include<stdint.h>
#include "../setup/pic.h"
#include "../InlineAssembly/inline.h"


void get_sector(uint32_t lba, void *buffer);

void wait_ready(){
    while((inb(0x1F7) & 0x80));
}

void wait_read(){
   while ((inb(0x1F7) & 0x88) != 0x08);

}


void get_sector(uint32_t lba, void *buffer){
    wait_ready();

    outb(0x1F2,1); //Sector Count


    outb(0x1F3, (uint8_t)(lba)); // First 8 bits
    outb(0x1F4, (uint8_t)(lba>>8)); // Middle 8 bits
    outb(0x1F5, (uint8_t)(lba>>16)); // High 8 bits
    outb(0x1F6, 0xE0 | ((uint8_t)(lba>>24)) & 0x0F); // Last 4-bits

    outb(0x1F7, 0x20);

    wait_read();

    insw(0x1F0, buffer, 256);

}

