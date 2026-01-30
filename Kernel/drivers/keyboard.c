#include<stdint.h>
#include<stdbool.h>
#include "../setup/pic.h"
#include "../std/stdFunctions.h"

bool shift= false;

unsigned char ascii[256] =
	{
		0x0, 0x0, '1', '2', '3', '4', '5', '6',		// 0 - 7
		'7', '8', '9', '0', '-', '=', 0x0, 0x0,		// 8 - 15
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',		// 16 - 23
		'o', 'p', '[', ']', '\n', 0x0, 'a', 's',	// 24 - 31
		'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',		// 32 - 39
		'\'', '`', 0x0, ' ', 'z', 'x', 'c', 'v',	// 40 - 47
		'b', 'n', 'm', ',', '.', '/', 0x0, '*',		// 48 - 55
		0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,		// 56 - 63
		0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, '7',		// 64 - 71
		'8', '9', '-', '4', '5', '6', '+', '1',		// 72 - 79
		'2', '3', '0', '.'				// 80 - 83
	};



unsigned char shift_ascii[256] =
	{
		0x0, 0x0, '!', '@', '#', '$', '%', '^',		// 0 - 7
		'&', '*', '(', ')', '_', '+', 0x0, 0x0,		// 8 - 15
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',		// 16 - 23
		'O', 'P', '{', '}', '\n', 0x0, 'A', 'S',	// 24 - 31
		'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',		// 32 - 39
		'\'', '`', 0x0, ' ', 'Z', 'X', 'C', 'V',	// 40 - 47
		'B', 'N', 'M', '<', '>', '?', 0x0, '*',		// 48 - 55
		0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,		// 56 - 63
		0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, '7',		// 64 - 71
		'8', '9', '-', '4', '5', '6', '+', '1',		// 72 - 79
		'2', '3', '0', '.'				// 80 - 83
	};



void keyboard(){

    uint8_t scancode = inb(0x60);   //READING THE SCAN CODE FROM THE DATA PORT OF THE KEYBOARD CONTROLLER

    bool released= scancode & 0x80;
    uint8_t key= scancode & 0x7F;

    if(key==0x2A || key==0x36){
        shift= !released;
        goto eoi;
    
    }

    if(released){
        goto eoi;
    }


    char c;
    if(shift){
        c= shift_ascii[key];

    }

    else{
        c=ascii[key];
    }
    

    if(scancode<0x80){
        printk("%c", c);
    }
    

    //SENDING THE EOI (END OF INTERRUPT) COMMAND TO THE PIC'S

    //0x20 IS THE CODE TO SIGNAL EOI
    eoi:
        outb(0x20, 0x20);
        outb(0xA0, 0x20);


}