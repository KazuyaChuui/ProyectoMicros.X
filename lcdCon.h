/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _LCD_H
#define	_LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 8000000

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */


void setup_LCD();
void ready_LCD();
void command_LCD(unsigned char x);
void display_LCD(unsigned char data);
void display_string_LCD(unsigned char *data);
void second_line();
#endif	/* _LCD_H */

