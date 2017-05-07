/*
 * File:   alarm.c
 * Author: JesusRuiz
 *
 * Created on May 7, 2017, 1:55 PM
 */

#include <xc.h>
#include "alarm.h"
#include "keypadCon.h"

void alarm(){
    while(1){
        LEDAlarm = 1;

        if(Sensor2 != 0){
            Buzzer = 1;
        }  
        if(obtainedKey()){
            return;
        }
    }
}