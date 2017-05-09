/*
 * File:   status.c
 * Author: JesusRuiz
 *
 * Created on April 27, 2017, 11:37 AM
 */


#include <xc.h>
#include "status.h"

void pwmInit(){
    // Tosc = 1/8 Mhz = 0.000000125
    // PWM Period = 20ms
    // PWM Frequency = 1/PWM Period = 50Hz 
    PR2 = 0x9B; // PWM period 
    CCPR1L = 0x2F; // eight most significant bits of duty cycle 0%
    T2CON = 0x07; // 16 prescale
    CCP1CON = 0x3C; // Duty Cycle LSB 0c

}
void open(){
    CCPR1L = 0x5F;// 15 % de 625 que es el maximo valor
}
void close(){
    CCPR1L = 0x1F;// 5 % de 625
}