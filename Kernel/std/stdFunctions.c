#include<stdarg.h>
#include<stdint.h>

#define VGA 0xB8000






/*
THe printk currently supports:
    %c ----- For character
    %x ----- For Hexadecimal. ie. Binary to Hexadecimal

*/



int cursor_x=0;
int cursor_y=0;

char hex_chars[] = "0123456789ABCDEF";


void put_char(char c);

void print_hex8(uint8_t value)
{
    put_char(hex_chars[(int)((value >> 4) & 0xF)]); 
    put_char(hex_chars[(int)(value & 0xF)]);
}

void put_char(char c){
    volatile unsigned short *vga = (unsigned short*)VGA;
    unsigned short text = (0x0F << 8) | c;
    int address= cursor_x+ (cursor_y*80);

    vga[address]= text;
    cursor_x+=1;

}

void delete_char(){
    cursor_x-=1;
    volatile unsigned short *vga = (unsigned short*)VGA;
    unsigned short text = (0x0F << 8) | 0x00;
    int address= cursor_x+ (cursor_y*80);

    vga[address]= text;
    

}


void enterPress() {
    cursor_x=0;
    cursor_y=cursor_y+1;
}

void printk(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    
    
    int i = 0;
    while (*msg) {
        if(*msg=='\n'){
            cursor_y+=1;
            cursor_x=0;
            i+=1;
            msg+=1;
            continue;
        }

        if(*msg == '%'){
            msg+=1;
            if(*msg== 'c'){
                char c= (char)va_arg(args, int);
                put_char(c);
            }

            if(*msg == 'x'){
                uint32_t val = va_arg(args, uint32_t);
                print_hex8(val);
            }

        }

        

        else{
            put_char(*msg);
        }

        msg+=1;
          
        
    }
  
}



void clear_screen(){
    volatile unsigned short *vga= (unsigned short*)VGA;

    unsigned short blank= (0x0F)<<8 | ' ';

    for(int i=0;i <80*25; i++){
        vga[i]=blank;
    }

    cursor_x=0;
    cursor_y=0;
}