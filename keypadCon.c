/*
 * File:   keypadCon.c
 * Author: JesusRuiz
 *
 * Created on May 3, 2017, 10:30 PM
 */


#include <xc.h>
#include "keypadCon.h"

#define fila1   LATCbits.LATC0
#define fila2   LATCbits.LATC1
#define fila3   LATEbits.LATE2
#define fila4   LATCbits.LATC3
#define columna1    PORTCbits.RC4
#define columna2    PORTCbits.RC5
#define columna3    PORTCbits.RC6
#define columna4    PORTCbits.RC7

unsigned char getKey(){
    
    fila1 = 0;
    fila2 = 1;
    fila3 = 1;
    fila4 = 1;
    __delay_ms(25);
    if(columna1 == 0) return '1';
    if(columna2 == 0) return '2';
    if(columna3 == 0) return '3';
    if(columna4 == 0) return 'A';
    
    fila1 = 1;
    fila2 = 0;
    fila3 = 1;
    fila4 = 1;
    __delay_ms(25);
    if(columna1 == 0) return '4';
    if(columna2 == 0) return '5';
    if(columna3 == 0) return '6';
    if(columna4 == 0) return 'B';
    
    fila1 = 1;
    fila2 = 1;
    fila3 = 0;
    fila4 = 1;
    __delay_ms(25);
    if(columna1 == 0) return '7';
    if(columna2 == 0) return '8';
    if(columna3 == 0) return '9';
    if(columna4 == 0) return 'C';
    
    fila1 = 1;
    fila2 = 1;
    fila3 = 1;
    fila4 = 0;
    __delay_ms(25);
    if(columna1 == 0) return '*';
    if(columna2 == 0) return '0';
    if(columna3 == 0) return '#';
    if(columna4 == 0) return 'D';
    
    return 0xFF;
}

void ground(){
    fila1 = 0;
    fila2 = 0;
    fila3 = 0;
    fila4 = 0;
}

unsigned char obtainedKey(){
    ground();
    unsigned char key_presionada = 0xFF;   
    do{
        key_presionada = getKey();
    }
    while(key_presionada == 0xFF);  //Hasta que la tecla este presionada
    
    while(getKey() != 0xFF); //Hasta que la tecla se suelte
    return key_presionada;
}