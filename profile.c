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

unsigned char eeprom_r(unsigned int address){
    EEADR = address;    //Carga la direccion de la eeprom que se leera
    EEADRH = address >> 8;  //2MSB
	EECON1bits.CFGS = 0;// allow access to EEPROM
	EECON1bits.EEPGD = 0;//to have access
	EECON1bits.RD = 1;  //Empezar a leer
    NOP();
    NOP();
    return EEDATA;  //Saca lo leido
}
void eeprom_w(unsigned int address, unsigned char value){
    EEADR = address;    //Carga la direccion de la eeprom a la que se quiere escribir LSB
    EEADRH = address >> 8;// 2MSB
    EEDATA = value;     //Carga la informaciona eedata
    EECON1bits.EEPGD =0;    //Para darle acceso a la eeprom
    EECON1bits.CFGS = 0;    //''
    EECON1bits.WREN = 1;    //Para habilitar la operacion de escritura
    INTCONbits.GIE = 0 ; //disable interruptions
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;    //Para empezar a escribir
    while(EECON1bits.WR); // hasta que este completo
    INTCONbits.GIE = 1; // reenable interruptions
    EECON1bits.WREN = 0;    //deshabilita escritura
    
}
unsigned char readPassword(unsigned char address){
    volatile unsigned char value;
    value = eeprom_r(address);  //lee de la eeprom
    return value;
}
void writePassword(unsigned char value, unsigned char address){
    eeprom_w(address, value);    //escribe a la eeprom
}
void profile(){
    unsigned int i = 0;
    ready_LCD();
    display_string_LCD("Which letter do");
    second_line_LCD();
    display_string_LCD("U Prefer A B C D");
    writePassword(obtainedKey(),0x20);      //Guarda usuario
    clear_LCD();
    first_line_LCD();
    display_string_LCD("Introduce Psswd");
    second_line_LCD();
    display_string_LCD("Only two keys");
    do{
        writePassword(obtainedKey(),0x00+1);    //Guarda passwd hasta que sean 2 keys
        i++;
    }while(i<2);
    clear_LCD();
    first_line_LCD();//regresa primera linea el cursor del LCD
}
unsigned char checkPassword(){
    unsigned char i = 0;

    do{
        unsigned char pass = readPassword(0x00+1);  //asigna key leida de eeprom correspondiente a pass
        if(obtainedKey() == pass){  //Verifica que la key leida sea igual a la presionada por el teclado
            return 1;        
        }else if((i<2) && obtainedKey() != pass){//En dado caso de que ya leyo las dos keys de pass y no son correctas
            return 0;
        }
        i++;
    }while(i<2);
    
}