// PIC24FJ128GA010 Configuration Bit Settings
// 'C' source line config statements
// CONFIG2
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config OSCIOFNC = ON            // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as port I/O (RC15))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)
// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog Timer is enabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)
#include <xc.h>
int main(void) {
    unsigned portValue = 0x01;
    unsigned portValue1 = 0x0007;
    char current6 = 0, prev6 = 0;
    char current13 = 0, prev13 = 0;
    char direction = 1;
    TRISA = 0x0000;
    TRISD = 0xFFFF;
    int value = 1;
    unsigned char kolejka[] = {
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,
    0x81,0x82,0x84,0x88,0x90,0xA0,0xC0,0xC1,
    0xC2,0xC4,0xC8,0xD0,0xE0,0xE1,0xE2,0xE4,
    0xE8,0xF0,0xF1,0xF2,0xF4,0xF8,0xF9,0xFA,
    0xFC,0xFD,0xFE,0xFF
    };
    int i = 0;
    unsigned char randGen = 0b1110011; 

    while (1) {
        switch (value) {
            case 1:
                LATA = portValue;
                portValue++;
                if (portValue == 0xFF) portValue = 0;
                break;
            case 2:
                LATA = portValue;
                portValue--;
                if (portValue == 0) portValue = 0xFFFF;
                break;
            case 3:
                LATA = portValue ^ (portValue >> 1);
                portValue++;
                break;
            case 4:
                LATA = portValue ^ (portValue >> 1);
                portValue--;
                break;
            case 5:
                LATA = ((portValue / 10) << 4) | (portValue % 10);
                portValue++;
                if (portValue > 99) portValue = 0;
                break;
            case 6:
                LATA = ((portValue / 10) << 4) | (portValue % 10);
                portValue--;
                if (portValue > 99) portValue = 99;
                break;
            case 7:
                LATA = portValue1;
                if (direction)
                    portValue1 <<= 1;
                else
                    portValue1 >>= 1;
                if (portValue1 == 0xE0)
                    direction = 0;
                else if (portValue1 == 0x07)
                    direction = 1;
                break;
 
            case 8:
                LATA = kolejka[i];
                i++;
                if (i >= sizeof(kolejka)) i = 0;
                break;
 
            case 9:
                randGen = (randGen >> 1) ^ ((randGen & 1) * 0x1B);
                LATA = randGen;
                break;
        }
        prev6 = PORTDbits.RD6;
        prev13 = PORTDbits.RD13;
        __delay32(1500000);
        current6 = PORTDbits.RD6;
        current13 = PORTDbits.RD13;
        if(prev6 == 1 && current6 == 0){
            value++;
            if(value > 9){
                value = 1;
            }
            portValue = 1;
        }
        if(prev13 == 1 && current13 == 0){
            value--;
            if(value < 1){
                value = 9;
            }
            portValue = 1;
        }
    }
    return 0;
}
