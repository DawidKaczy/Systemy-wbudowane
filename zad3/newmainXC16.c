// Konfiguracja mikrokontrolera PIC24FJ128GA010

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
}

int main(void) {
    init();

    unsigned long value_poten;
    unsigned int nastawa = 512;     //po?owa
    int alarm = 0;                  
    int miganie = 0;        

    while (1) {
        value_poten = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);
        
        //je?eli wieksze ni? po?owa i alarmu nie ma to miga 5 razy
        if (value_poten > nastawa && alarm == 0) 
        {
            alarm = 1;
            miganie = 1;

            for (int i = 0; i < 5; i++) 
            {
                value_poten = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);
                if (value_poten <= nastawa || BUTTON_IsPressed(BUTTON_S4)) 
                {
                    alarm = 0;
                    LATA = 0x00;
                    break;
                } 
                // w innym przypadku gasimy 
                else 
                {
                    LATA = 0x01;           
                    __delay32(2000000);
                    LATA = 0x00;           
                    __delay32(2000000);
                }
            }

            miganie = 0;
        }
        
        //jak alarm dzia?a i miganie gasnie to zaplaja si? wszystko
        if (alarm == 1 && miganie == 0) 
        {
            LATA = 0xFF;
        }
        //jak potencjometr jest poni?ej po?owy to ga?nie wszystko
        if (value_poten <= nastawa) 
        {
            alarm = 0;
            LATA = 0x00;
        }
        //jak wciskamy przycisk to resetue si? alarm
        if (BUTTON_IsPressed(BUTTON_S3)) 
        {
            __delay32(10000); 
            alarm = 0;
            LATA = 0x00;
        }
    }

    return 0;
}
