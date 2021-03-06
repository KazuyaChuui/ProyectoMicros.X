/*
 * File:   menu.c
 * Author: JesusRuiz
 *
 * Created on April 27, 2017, 11:38 AM
 */


#include <xc.h>
#include "menu.h"
#include "lcdCon.h"
#include "status.h"
#include "keypadCon.h"
#include "profile.h"

void welcome(){
    ready_LCD();
    display_string_LCD("1.Door 2.LogOut");
}

void menu(){
    while(1){
        flag = 0;//Asigna la bandera a 0
        if(obtainedKey() == '1'){//Si el teclado se presiona 1
            clear_LCD();
            first_line_LCD();
            display_string_LCD("1.Unlock 2.Lock");
            if(obtainedKey() == '1'){
                open();//abre el servo motor gracias al PWM
                clear_LCD();
                first_line_LCD();
                display_string_LCD("-Door Unlocked-");
                second_line_LCD();
                display_string_LCD("A to GoBack");
                if(obtainedKey() == 'A'){//Regresa al menu
                    clear_LCD();
                    return;
                }  
            }else if(obtainedKey() == '2'){
                close();//Cierra el servo motor gracias al PWM
                clear_LCD();
                first_line_LCD();
                display_string_LCD("-Door Locked-");
                second_line_LCD();
                display_string_LCD("A to GoBack");
                if(obtainedKey() == 'A'){
                    clear_LCD();
                    return;
                }  
            }
        }else if(obtainedKey() == '2'){
            clear_LCD();
            ready_LCD();
            display_string_LCD("Bye user ");
            display_LCD(readPassword(0x20));
            second_line_LCD();
            display_string_LCD("Alarm Active");
            __delay_ms(2500);//Para que se alcance a leer el mensaje anterior
            flag = 1;//levanta la bandera para salir del menu
            return;
        }
    }
    return;
}
