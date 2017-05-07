/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef alarm_H
#define	alarm_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define Buzzer  PORTAbits.RA0
#define LEDAlarm    PORTEbits.RE1
#define Sensor2 PORTBbits.RB2

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */
void alarm();
#endif	/* alarm_H */

