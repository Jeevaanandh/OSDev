#define VGA 0xB8000

int cursor_x=0;
int cursor_y=0;


void printk(const char *msg) {
    volatile unsigned short *vga = (unsigned short*)VGA;
    
    int i = 0;
    while (msg[i]) {
        int address= cursor_x+ (cursor_y*80);
        if(msg[i]=='\n'){
            cursor_y+=1;
            cursor_x=0;
            i+=1;
            continue;
        }

        
        unsigned short text = (0x0F << 8) | msg[i];
        

        vga[address]= text;
        cursor_x+=1;
        i++;
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