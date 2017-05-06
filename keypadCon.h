
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _keypadCon_H
#define	_keypadCon_H

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

unsigned char getKey();
unsigned char obtainedKey();
void ground();
#endif	/* keypadCon_H */

