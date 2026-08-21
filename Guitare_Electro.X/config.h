/* INCLUDES */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


/* DEFINITIONS */
#define E2_CHORD    82
#define A2_CHORD    110
#define D3_CHORD    147
#define G3_CHORD    196
#define B3_CHORD    247
#define E4_CHORD    330

#define SAMPLE_LEN  512
#define SAMPLE_FREQ 1953

#define CHAR_0 0b00111111
#define CHAR_1 0b00000110
#define CHAR_2 0b01011011
#define CHAR_3 0b01001111
#define CHAR_4 0b01100110
#define CHAR_5 0b01101101
#define CHAR_6 0b01111101
#define CHAR_7 0b00000111
#define CHAR_8 0b01111111
#define CHAR_9 0b01101111
#define CHAR_A 0b01110111
#define CHAR_B 0b01111100
#define CHAR_C 0b00111001
#define CHAR_D 0b01011110
#define CHAR_E 0b01111001
#define CHAR_F 0b01110001
#define CHAR_G 0b00111101
#define CHAR_H 0b01110100
#define CHAR_I 0b00000100
#define CHAR_J 0b00011110
#define CHAR_K 0b01110101
#define CHAR_L 0b00111000
#define CHAR_M 0b01010101
#define CHAR_N 0b01010100
#define CHAR_O 0b01011100
#define CHAR_P 0b01110011
#define CHAR_Q 0b01100111
#define CHAR_R 0b01010000
#define CHAR_S 0b01101101
#define CHAR_T 0b01111000
#define CHAR_U 0b00111110
#define CHAR_V 0b00011100
#define CHAR_W 0b01101010
#define CHAR_X 0b01110110
#define CHAR_Y 0b01101110
#define CHAR_Z 0b01011011

#define _XTAL_FREQ 8000000UL // 8 MHz


#define DISPLAY_CLK          LATCbits.LATC3
#define DISPLAY_DIO          LATCbits.LATC4
#define DISPLAY_CLK_TRIS     TRISCbits.TRISC3
#define DISPLAY_DIO_TRIS     TRISCbits.TRISC4

#define _ON      1
#define _OFF     0

#define VOL_BUTTON_DIR	TRISAbits.TRISA3	// direction of VOL_ENCODEUR BUTTON (OUTP)
#define VOL_ENC_A_DIR	TRISAbits.TRISA2	// direction of VOL_ENCODEUR A (OUTP)
#define VOL_ENC_B_DIR	TRISAbits.TRISA1	// direction of VOL_ENCODEUR B (OUTP)

#define VOL_BUTTON LATAbits.LAT3
#define VOL_ENC_A LATAbits.LAT2
#define VOL_ENC_B LATAbits.LAT1

#define FX_BUTTON_DIR	TRISAbits.TRISA4	// direction of VOL_ENCODEUR BUTTON (OUTP)
#define FX_ENC_A_DIR	TRISAbits.TRISA5	// direction of VOL_ENCODEUR A (OUTP)
#define FX_ENC_B_DIR	TRISEbits.TRISE0	// direction of VOL_ENCODEUR B (OUTP)

#define FX_BUTTON LATAbits.LAT4
#define FX_ENC_A LATAbits.LAT5
#define FX_ENC_B LATEbits.LAT0

#define SS_PGA LATBbits.LATB3
#define MUTE_PGA LATBbits.LATB4

#define PROG0 LATBbits.LATB0
#define PROG1 LATDbits.LATD7
#define PROG2 LATDbits.LATD6
#define PROG3 LATDbits.LATD5

#define M_PI       3.14159265358979323846

#define VOL_READ_PORT   PORTAbits.RA1
#define VOL_ENC_SEUIL   3

#define FX_READ_PORT    PORTEbits.RE0
#define FX_ENC_SEUIL    3

#define volume_max 20
#define program_count 16

#define DIO     TRISCbits.TRISC4
#define SCK     TRISCbits.TRISC3



