// PIC24FJ128GA010 Configuration Bit Settings

#pragma config POSCMOD = XT
#pragma config OSCIOFNC = ON
#pragma config FCKSM = CSDCMD
#pragma config FNOSC = PRI
#pragma config IESO = ON

#pragma config WDTPS = PS32768
#pragma config FWPSA = PR128
#pragma config WINDIS = ON
#pragma config FWDTEN = ON
#pragma config ICS = PGx2
#pragma config GWRP = OFF
#pragma config GCP = OFF
#pragma config JTAGEN = OFF

#include "xc.h"
#include "libpic30.h"
#include "adc.h"
#include "buttons.h"

void init(void) {
    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
    ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER);
    TRISA = 0x0000;
    BUTTON_Enable(BUTTON_S3);
    BUTTON_Enable(BUTTON_S4);
}

int main(void) {
    init();
    unsigned portValue1 = 0x0007;
    
    
    char direction = 1;
    
    
    unsigned char value = 1;
    unsigned long value_poten;
    unsigned long opoznienie;
    unsigned char ok;
    unsigned char kolejka[] = {
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,
    0x81,0x82,0x84,0x88,0x90,0xA0,0xC0,0xC1,
    0xC2,0xC4,0xC8,0xD0,0xE0,0xE1,0xE2,0xE4,
    0xE8,0xF0,0xF1,0xF2,0xF4,0xF8,0xF9,0xFA,
    0xFC,0xFD,0xFE,0xFF
    };
    int i = 0;

    while(1) {
        value_poten = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);

        ok = value_poten / 205; //1024 / 5 = 204.8  zaokr?glamy w dó? do 205, ?eby równo podzieli? zakres.
        switch(ok) {
            case 0: opoznienie = 100000;    break;
            case 1: opoznienie = 300000;    break;
            case 2: opoznienie = 1000000;   break; 
            case 3: opoznienie = 1500000;   break; 
            case 4: opoznienie = 2500000;   break; 
        }

        switch(value) {
            case 1:
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
            case 2:
                LATA = kolejka[i++];
                if (i >= sizeof(kolejka)) i = 0;
                break;
        }

        __delay32(opoznienie);

        if (BUTTON_IsPressed(BUTTON_S3)) {
            __delay32(1000);
            value = 1;
        }

        if (BUTTON_IsPressed(BUTTON_S4)) {
            __delay32(1000);
            value = 2;
        }
    }
    return 0;
}
