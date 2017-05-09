/*
 * File:   mainCode.c
 * Author: JesusRuiz
 *
 * Created on April 21, 2017, 4:50 PM
 */

#define LEDBu   PORTAbits.RE0 
#define LEDLuz    PORTAbits.RA5 
#define Sensor1 PORTBbits.RB1
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

void interrupt backup(void);
void interrupt low_priority luz(void);

void main(void) {
    OSCCON = 0x70;      //Oscilador 8MHz
    CMCON = 0xFF;       //Apaga comparadores puerto D
    CVRCONbits.CVREN = 0;//Apaga comparador de voltaje
    ADCON1 = 0x0F;      //Puertos digitales
    INTCON2bits.RBPU = 0;//Pullup resistor puertoB
    RCONbits.IPEN = 1; //prioridades activadas
    INTCONbits.GIEH = 1; // prioridades altas activadas
    INTCONbits.GIEL = 1; // prioridades bajas activadas

    
    INTCON3bits.INT2IP=1;//INT2 como alta prioridad
    INTCON2bits.INTEDG2 = 1;//activada por rising edge
    INTCON3bits.INT2IE = 1; //activa la interrupcion
    
    //configuracion de INT1 activada por RB1
    INTCON3bits.INT1IP = 0; //prioridad baja
    INTCON2bits.INTEDG1 = 1;//activada por rising edge
    INTCON3bits.INT1IE=1;//activa la interrupcion
    
    unsigned char key;
    
    PORTA = 0x00;   //Inicializa puertoA
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    LATA = 0x00;    //Limpia puertoA
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    TRISA = 0x00;   //Asigna entradas/salidas
    TRISB = 0x07;
    TRISC = 0xF0;
    TRISD = 0x00;
    TRISE = 0x00;
    
    setup_LCD();    //Inicializa LCD
    pwmInit();      //Inicializa PWM
    while(1){
        //preset();
        if(readPassword(0x20) != 'A' &&     //Verifica si hay usuario existente
           readPassword(0x20) != 'B' &&
           readPassword(0x20) != 'C' && 
           readPassword(0x20) != 'D')
        {
            profile();                      //Crea nuevo usuario
        }else{
            ready_LCD();                    //Verifica si LCD esta listo 
            display_string_LCD("Enter Password");//Despliega string en LCD
            alarm();                        //Inicializa la alarma
            if(checkPassword() != 1){       //Checa si la contrasena es correcta
                    clear_LCD();
                    ready_LCD();
                    display_string_LCD("Wrong Password");
            }else{
                while(1){
                    Buzzer = 0;                     //Apaga el buzzer
                    LEDAlarm = 0;                   //Apaga led alarma
                    clear_LCD();
                    ready_LCD();
                    display_string_LCD("Alarm Deactiv");
                    __delay_ms(1500);               //delay para alcanzar a desplegar msg anterior
                    clear_LCD();
                    ready_LCD();
                    display_string_LCD("Welcome User ");
                    display_LCD(readPassword(0x20));  //Lee usuario nombre
                    second_line_LCD();          //pasa a segunda linea de LCD
                    welcome();                  //DEspliega msg bienvenida
                    menu();                     //Despliega menu
                    if(flag == 1){              //Para salir del while checa la bandera flag
                        return;
                    }
                }
            }
        }          
    }
    
    return;
}
void interrupt low_priority luz(void){//RB1=1
 INTCON3bits.INT1IF = 0;//limpiamos la bandera

 PORTAbits.RA5=1;
 __delay_ms(3000);
 PORTAbits.RA5=0;
 
    return;
}
void interrupt backup(void){ //RB2 pasa de 0 a 1 pin35
INTCON3bits.INT2IF = 0;//limpiar bandera
PORTAbits.RA5=0;//apagar luces

PORTEbits.RE0=1;
__delay_ms(500);
PORTEbits.RE0=0;
__delay_ms(500);
PORTEbits.RE0=1;
__delay_ms(500);
PORTEbits.RE0=0;
__delay_ms(500);
PORTEbits.RE0=1;
__delay_ms(500);
PORTEbits.RE0=0;
__delay_ms(500);
return;
}