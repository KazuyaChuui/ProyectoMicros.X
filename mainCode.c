/*
 * File:   mainCode.c
 * Author: JesusRuiz
 *
 * Created on April 21, 2017, 4:50 PM
 */

#define LED1    PORTAbits.RA4
#define LED2    PORTAbits.RA5
#define Sensor1 PORTBbits.RB0
#define Backup  PORTBbits.RB2

#include <xc.h>
#include "lcdCon.h"
#include "profile.h"
#include "status.h"
#include "menu.h"
#include "keypadCon.h"
#include "alarm.h"


#pragma config OSC = IRCIO67
#pragma config MCLRE = ON
#pragma config PBADEN = OFF
#pragma config LVP = OFF
#pragma config WDT = OFF

void main(void) {
    OSCCON = 0x70;
    CMCON = 0xFF;
    CVRCONbits.CVREN = 0;
    ADCON1 = 0x0F;
    INTCON2bits.RBPU = 0;
    
    unsigned char key;
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    TRISA = 0x00;
    TRISB = 0x03;
    TRISC = 0xF0;
    TRISD = 0x00;
    TRISE = 0x00;
  
    setup_LCD();
    pwmInit();
    while(1){
        //preset();
        if(readPassword(0x20) != 'A' && 
           readPassword(0x20) != 'B' &&
           readPassword(0x20) != 'C' && 
           readPassword(0x20) != 'D')
        {
            profile();
        }else{
            ready_LCD();
            display_string_LCD("Enter Password");
            alarm();
            if(checkPassword() != 1){
                    clear_LCD();
                    ready_LCD();
                    display_string_LCD("Wrong Password");
            }else{
                while(1){
                    Buzzer = 0;
                    LEDAlarm = 0;
                    clear_LCD();
                    ready_LCD();
                    display_string_LCD("Alarm Deactiv");
                    __delay_ms(1500);
                    clear_LCD();
                    ready_LCD();
                    display_string_LCD("Welcome User ");
                    display_LCD(readPassword(0x20));
                    second_line_LCD();
                    welcome();
                    menu();
                    if(flag == 1){
                        return;
                    }
                }
            }
        }          
    }
    
    return;
}
