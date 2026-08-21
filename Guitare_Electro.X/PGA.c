/*
 * File:   PGA.c
 * Author: Admin
 *
 * Created on 11 juin 2025, 10:02
 */


#include <xc.h>
#include "config.h"
#include "functions.h"

void init_PGA(void){
    
    ANSELBbits.ANSELB5 = 0;
    ANSELBbits.ANSELB4 = 0;
    ANSELBbits.ANSELB3 = 0;
    ANSELBbits.ANSELB2 = 0;
    ANSELBbits.ANSELB1 = 0;
    
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB1 = 0;

    SS_PGA = 1;
    MUTE_PGA = 1;
    
}