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
        LEDAlarm = 1;//enciende el led

        if(Sensor2 != 0){//si el sensor detecta algo
            Buzzer = 1;
        }  
        if(obtainedKey()){//si se presiona cualquier tecla sale del while
            return;
        }
    }
}