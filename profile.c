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

unsigned char readPassword(unsigned char address){
    volatile unsigned char value;
    value = eeprom_read(address);
    return value;
}
void writePassword(unsigned char value, unsigned char address){
    eeprom_write(address, value);     
}
void preset(){
    writePassword('C',0x00);
    writePassword('A',0x01);
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
    display_string_LCD("Which temp");
    second_line_LCD();
    display_string_LCD("range 1-9");
    writePassword(obtainedKey(),0x40);
    clear_LCD();
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