#pragma config POSCMOD = XT     
#pragma config OSCIOFNC = ON    
#pragma config FCKSM   = CSDCMD 
#pragma config FNOSC   = PRI   
#pragma config IESO    = ON     
#pragma config WDTPS   = PS32768 
#pragma config FWPSA   = PR128   
#pragma config WINDIS  = ON      
#pragma config FWDTEN  = OFF    
#pragma config ICS     = PGx2   
#pragma config GWRP    = OFF     
#pragma config GCP     = OFF     
#pragma config JTAGEN  = OFF     
 
#include <xc.h>
#include <libpic30.h>
#include "buttons.h"   
#include "lcd.h"       
#include <string.h>    
 
 
#define SCROLL_DELAY 2500000  
 
void system_init(void) {
    LCD_Initialize();
    TRISA = 0x0000;    
    }
 
void uwaga(void) {
    for (int i = 0; i < 5; i++) {
        LCD_ClearScreen();
        LCD_PutString(" $$$ UWAGA $$$", 14);
        LCD_PutChar('\n');
        LCD_PutString(" $$$ UWAGA $$$", 14);
        LATA = 0xFFFF;
        __delay32(1000000);
 
        LCD_ClearScreen();
        LATA = 0x0000;
        __delay32(1000000);
        
        LCD_ClearScreen();
        LCD_PutString("   $$$ UWAGA $$$", 16);
        LCD_PutChar('\n');
        LCD_PutString("   $$$ UWAGA $$$", 16);
        LATA = 0xFFFF;
        __delay32(1000000);
 
        LCD_ClearScreen();
        LATA = 0x0000;
        __delay32(1000000);
        
        
    }
}

void plywanyNapis(void)
{
    const char *ad = "SALE \x7F\x7E UP \x7F\x7E NOW ";
    size_t len = strlen(ad);
    char buf[17];

    for (size_t step = 0; step < 30; step++) {
        size_t offset = step % len;

        for (int i = 0; i < 16; i++) {
            buf[i] = ad[(offset + i) % len];
        }
        buf[16] = '\0';

        LCD_ClearScreen();
        LCD_PutString(buf, 16);
        __delay32(SCROLL_DELAY);
    }
}

void kolejnyNapis(void) {
    LCD_ClearScreen();
    for (int i = 0; i < 5; i++) {
        LCD_ClearScreen();
        LCD_PutString(" UP TO 50% OFF!", 16);
        LCD_PutChar('\n');
        LCD_PutString(" UP TO 50% OFF!", 16);
        LATA = 0xFFFF;
        __delay32(1000000);
        LCD_ClearScreen();
        __delay32(1000000);
    }
    
    
    
    
}
 
int main(void) {
 
    while (1){
    system_init();
    uwaga();
    plywanyNapis();
    kolejnyNapis();
    }
    return 0;
}