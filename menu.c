/*
 * File:   menu.c
 * Author: JesusRuiz
 *
 * Created on April 27, 2017, 11:38 AM
 */


#include <xc.h>
#include "menu.h"
#include "lcdCon.h"
#include "keypadCon.h"
#include "status.h"


void menu(){
    while(1){
        display_string_LCD("1.Door 2.EndSess");
        ready_LCD();
        second_line_LCD();
        if(obtainedKey() == '1'){
            clear_LCD();
            first_line_LCD();
            display_string_LCD("*.Open #.Close");
            ready_LCD();
            if(obtainedKey() == '*'){
                open();
                second_line_LCD();
                display_string_LCD("Opened");
                ready_LCD();
                return;
            }else if(obtainedKey() == '#'){
                close();
                second_line_LCD();
                display_string_LCD("Closed");
                ready_LCD();
                return;
            }
        }else if(obtainedKey() == '2'){
            clear_LCD();
            first_line_LCD();
            display_string_LCD("Session Ended");
            ready_LCD();
            return;
        }
    }
}
