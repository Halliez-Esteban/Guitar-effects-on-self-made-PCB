/*
 * File:   V1000.c
 * Author: Admin
 *
 * Created on 11 juin 2025, 10:12
 */


#include <xc.h>
#include "config.h"
#include "functions.h"

void init_V1000(void){
    
    ANSELBbits.ANSELB0 = 0;
    
    TRISBbits.TRISB0 = 0;
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    
    PROG0 = 0;
    PROG1 = 0;
    PROG2 = 0;
    PROG3 = 0;
    
}