/*
 * File:   profile.c
 * Author: JesusRuiz
 *
 * Created on April 27, 2017, 11:34 AM
 */


#include <xc.h>
#include "profile.h"
#include "lcdCon.h"
#include "keypadCon.h"

unsigned char eeprom_r(unsigned char address){
    EEADR = address;
	EECON1bits.CFGS = 0;// allow access to EEPROM
	EECON1bits.EEPGD = 0;//to have access
	EECON1bits.RD = 1;
    NOP();
    NOP();
    return EEDATA;
}
void eeprom_w(unsigned char address, unsigned char value){
    EEADR = address;
    EEDATA = value;
    EECON1bits.EEPGD =0;
    EECON1bits.CFGS = 0;
    INTCONbits.GIE = 0; //disable interruptions
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    while(EECON1bits.WR); // hasta que este completo
    INTCONbits.GIE = 1; // reenable interruptions
    EECON1bits.WREN = 0;
    
}
unsigned char readPassword(unsigned char address){
    volatile unsigned char value;
    value = eeprom_r(address);
    return value;
}
void writePassword(unsigned char value, unsigned char address){
    eeprom_w(address, value);     
}
void profile(){
    unsigned int i = 0;
    ready_LCD();
    display_string_LCD("Which letter do");
    second_line_LCD();
    display_string_LCD("U Prefer A B C D");
    writePassword(obtainedKey(),0x20);
    clear_LCD();
    first_line_LCD();
    display_string_LCD("Introduce Psswd");
    second_line_LCD();
    display_string_LCD("Only two keys");
    do{
        writePassword(obtainedKey(),0x00+1);
        i++;
    }while(i<2);
    clear_LCD();
    first_line_LCD();
}
unsigned char checkPassword(){
    unsigned char i = 0;

    do{
        unsigned char pass = readPassword(0x00+1);
        if(obtainedKey() == pass){
            return 1;        
        }else if((i<2) && obtainedKey() != pass){
            return 0;
        }
        i++;
    }while(i<2);
    
}