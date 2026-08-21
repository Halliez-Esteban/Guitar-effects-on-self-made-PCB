#include "config.h"
#include "functions.h"


volatile int COUNTER = 0;
volatile int COUNTER2 = 0;

char EFFET_1[12] = {CHAR_M,CHAR_E,CHAR_D,CHAR_I,CHAR_U,CHAR_M,0x00,0x00,0x00,0x00,0x00,0x00};
char EFFET_2[12] = {CHAR_C,CHAR_H,CHAR_A,CHAR_M,CHAR_B,CHAR_R,CHAR_7,CHAR_B,0x00,0x00,0x00,0x00};
char EFFET_3[12] = {CHAR_R,CHAR_O,CHAR_O,CHAR_M,CHAR_3,CHAR_B,0x00,0x00,0x00,0x00,0x00,0x00};
char EFFET_4[12] = {CHAR_C,CHAR_H,CHAR_A,CHAR_M,CHAR_B,CHAR_E,CHAR_R,CHAR_2,0x00,0x00,0x00,0x00};
char EFFET_5[12] = {CHAR_R,CHAR_E,CHAR_V,CHAR_E,CHAR_R,CHAR_S,CHAR_3,CHAR_B,0x00,0x00,0x00,0x00};
char EFFET_6[12] = {CHAR_G,CHAR_A,CHAR_T,CHAR_E,CHAR_D,CHAR_4,CHAR_B,0x00,0x00,0x00,0x00,0x00};
char EFFET_7[12] = {CHAR_R,CHAR_O,CHAR_O,CHAR_M,CHAR_2,CHAR_A,0x00,0x00,0x00,0x00,0x00,0x00};
char EFFET_8[12] = {CHAR_S,CHAR_P,CHAR_R,CHAR_I,CHAR_N,CHAR_G,CHAR_3,CHAR_B,0x00,0x00,0x00,0x00};
char EFFET_9[12] = {CHAR_P,CHAR_H,CHAR_A,CHAR_S,CHAR_E,CHAR_R,CHAR_1,0x00,0x00,0x00,0x00,0x00};
char EFFET_10[12] = {CHAR_F,CHAR_L,CHAR_A,CHAR_N,CHAR_G,CHAR_E,CHAR_R,CHAR_2,0x00,0x00,0x00,0x00};
char EFFET_11[12] = {CHAR_D,CHAR_E,CHAR_L,CHAR_A,CHAR_Y,CHAR_7,0x00,0x00,0x00,0x00,0x00,0x00};
char EFFET_12[12] = {CHAR_C,CHAR_H,CHAR_O,CHAR_R,CHAR_U,CHAR_S,CHAR_4,0x00,0x00,0x00,0x00,0x00};
char EFFET_13[12] = {CHAR_E,CHAR_A,CHAR_R,CHAR_L,CHAR_R,CHAR_E,CHAR_F,CHAR_4,0x00,0x00,0x00,0x00};
char EFFET_14[12] = {CHAR_A,CHAR_M,CHAR_B,CHAR_4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
char EFFET_15[12] = {CHAR_D,CHAR_E,CHAR_L,CHAR_A,CHAR_Y,CHAR_3,0x00,0x00,0x00,0x00,0x00,0x00};
char EFFET_16[12] = {CHAR_D,CHAR_E,CHAR_L,CHAR_A,CHAR_Y,CHAR_1,0x00,0x00,0x00,0x00,0x00,0x00};

char* EFFETS_TAB[16] = {EFFET_1,EFFET_2,EFFET_3,EFFET_4,EFFET_5,EFFET_6,EFFET_7,EFFET_8,EFFET_9,EFFET_10,EFFET_11,EFFET_12,EFFET_13,EFFET_14,EFFET_15,EFFET_16};


volatile int current_volume = 0;
volatile int current_fx_index = 15;
char effet_str[12];
volatile int rolling_count=0;
volatile bool show_fx = true;

//volatile int ENCODEUR_PIN_B;
void __interrupt(irq(default)) ISR(void){
    
    
    if( IOCAFbits.IOCAF3 == _ON){
         vol_encoder_press();
         IOCAFbits.IOCAF3 = _OFF;
     }
    else if( IOCAFbits.IOCAF2 == _ON){
        show_fx = false;
        vol_encoder_rotating(&COUNTER, &current_volume);
        IOCAFbits.IOCAF2 = _OFF;
    }
    else if( IOCAFbits.IOCAF4 == _ON){
         fx_encoder_press();
         IOCAFbits.IOCAF4 = _OFF;
     }
    else if( IOCAFbits.IOCAF5 == _ON){
        show_fx=true;
        fx_encoder_rotating(&COUNTER2,&current_fx_index);
        //effet_str = EFFETS_TAB [current_fx_index];
         IOCAFbits.IOCAF5 = _OFF;
    }
    //check if the interrupt is caused by the pin RC0
    else if(PIR1bits.ADIF == 1) {
        
        // Clearing TMR0 flag & ADC flag
        PIR3bits.TMR0IF = 0;
        PIR1bits.ADIF = 0;
        
        LATBbits.LATB0 = !LATBbits.LATB0;
        
        adc_end();
    }
    /*else if(PIR3bits.TMR0IF == 1) {
        PIR3bits.TMR0IF = 0;
        LATBbits.LATB0 = 0;
    }*/
    
 }


void init() {
    
    
    OSCCON1bits.NOSC = 0b110;   // Set clock source to HFINTOSC
    OSCCON1bits.NDIV = 0b0000;  // Set clock divider to 1:1
    OSCFRQ = 0b0011; // 8 MHz
    
    UARTInit();
    init_interrupts();
    // init_tuner();
    display_init();
    init_encoder();
    
}


void init_interrupts() {   
    PIE0bits.IOCIE = 1;     // Enable interrupts on change
    INTCON0bits.GIE = 1;    // Enable all interrupts
}

void main() {
    
    strcpy(effet_str,EFFETS_TAB[0]);
    TRISBbits.TRISB0 = 0;
    LATBbits.LATB0 = 1;
    
    init();
    
    while(1) {
        
        //Affichage de l'effet sur le 7segments
        if(show_fx){
            
            display_print((effet_str[rolling_count]),(effet_str[(rolling_count+1)%12]),(effet_str[(rolling_count+2)%12]),(effet_str[(rolling_count+3)%12]),false);
            rolling_count=(rolling_count+1)%12;
            
        }
        //Affichage du volume sur le 7segments
        else{
            char* volume_str;
            volume_str = get_current_value_into_string(current_volume);
            display_print(0x00,CHAR_V, volume_str[0],volume_str[1],true);
            rolling_count=0;
            
        }
        
        __delay_ms(500);

    }
    
}