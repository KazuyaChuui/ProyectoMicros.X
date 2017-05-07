/*
 * File:   lcdCon.c
 * Author: JesusRuiz
 *
 * Created on April 27, 2017, 12:19 PM
 */


#include <xc.h>
#include "lcdCon.h"

#define RS  PORTAbits.RA1
#define RW  PORTAbits.RA2
#define E   PORTAbits.RA3

#define DB0 PORTDbits.RD0
#define DB1 PORTDbits.RD1
#define DB2 PORTDbits.RD2
#define DB3 PORTDbits.RD3
#define DB4 PORTDbits.RD4
#define DB5 PORTDbits.RD5
#define DB6 PORTDbits.RD6
#define DB7 PORTDbits.RD7

void command_LCD(unsigned char x);
void ready_LCD();

void setup_LCD(){
    E = 0;
    __delay_ms(250);
    command_LCD(0x38);
    __delay_ms(250);
    command_LCD(0x0F);
    ready_LCD();
    command_LCD(0x01);
    ready_LCD();
}

void command_LCD(unsigned char x){
    PORTD = x;
    RS = 0;
    RW = 0;
    E = 1;
    __delay_ms(.45);
    E = 0;
}

void ready_LCD(){
    TRISD = 0xFF;
    RS = 0;
    RW = 1;
    do{
        E = 1;
        __delay_ms(.45);
        E = 0;
    }while(DB7 == 1);
    TRISD = 0x00;
}

void display_LCD(unsigned char data){
    PORTD = data;
    RS = 1;
    RW = 0;
    E = 1;
    __delay_ms(.45);
    E = 0;
}

void display_string_LCD(unsigned char *data){
    RS = 1;
    while(*data){
        display_LCD(*data++);
    }
    ready_LCD();
}
void first_line_LCD(){
    command_LCD(0x20);
    ready_LCD();
}
void second_line_LCD(){
    command_LCD(0xC0);
    ready_LCD();
}
void clear_LCD(){
    command_LCD(0x01);
}
