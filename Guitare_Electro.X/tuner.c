#include "config.h"
#include "functions.h"

uint16_t curr_sample_index = 0;
uint8_t audio_data[SAMPLE_LEN];
uint16_t new_sum = 0;
uint16_t prev_sum = 0;
uint8_t p_status_chk = 0;
uint16_t period = 0;
uint16_t thld = 0;
float frequency = 0.0;

void init_tuner() {
    
    init_adc();
    init_tmr0();
    
}

void init_adc() {
    
    PIE1bits.ADIE = 1; // Enable interrupt
    PIR1bits.ADIF = 0; // Clear flag
    
    // Define ADC channel for RC0 (cf. p819 from DS)
    ADPCHbits.ADPCH4 = 1;
    TRISCbits.TRISC0 = 1;
    ANSELCbits.ANSELC0 = 1;

    
    // Set ADC reference  
    ADREFbits.NREF = 0b0;   // Low ref
    ADREFbits.PREF0 = 0b0;  // High ref (0)
    ADREFbits.PREF1 = 0b0;  // High ref (1)
    
    // ADC Control register
    ADCON0bits.ON = 0b1; // Enable ADC module
    ADCON0bits.CS = 0b0; // Set clock to ADC clock division
    ADCON0bits.FM = 0b0; // Left justified result
  
   
    // ADC clock control
    ADCLK = 0b010; // ADC clock frequency = Fosc / 6
  
    // Configure ADC toggle on TMR0
    ADACT = 0b00000010;
  
    // Start first conversion to start the process
    ADCON0bits.GO = 1;
}

void init_tmr0() {
    
    PIE3bits.TMR0IE = 1;        // Enable interrupt
    PIR3bits.TMR0IF = 0;        // Clear flag
    
    T0CON0bits.MD16 = 0;        // Set TMR0 to 8 bit mode
    T0CON0bits.OUTPS = 0b0;     // Set to 1:1 the post scaler
    
    T0CON1bits.CS = 0b010;      // Clock source: HFINTOSC
    T0CON1bits.ASYNC = 0;       // Synchronize with Fosc/4
    T0CON1bits.CKPS = 0b0011;   // Set prescaler to 1:4    
    
    TMR0H = 0xFF;               // Set TMR0H to 255 (match value)
    TMR0L = 0x00;               // Set TMR0L to 0 (to start clock)
    
    T0CON0bits.T0EN = 1;          // Start timer0
    
    // T0CS FOSC/4; T0CKPS 1:1; T0ASYNC not_synchronized; 
    /*T0CON1bits.CS = 0b010; // Set clock source to Fosc/4
    T0CON1bits.ASYNC = 1; // Not synchronized to system clocks
  
    // TMR0 to 223 operations 
    TMR0H = 0x00;//0xDF;
    TMR0L = 0x00;
  
    // T0OUTPS 1:8; T0EN enabled; T016BIT 8-bit; 
    T0CON0bits.T0EN = 1; // Enable TMR0
    T0CON0bits.OUT = 0; // 8 bits timer
    T0CON0bits.OUTPS = 0b0000; // Set post-scaler to 16
    
    //Start timer
    T0CON0bits.T0EN = 1;
    */
}


uint16_t get_frequency(uint8_t audio_data[]) {
    
    UARTPrint("-----------------------");
  
    
    for (int16_t i = 0; i < SAMPLE_LEN; i++) {
        UARTPrintInt(audio_data[i]);
    }
    
    
    
    for (int16_t i = 0; i < SAMPLE_LEN; i++) {
        // Autocorrelation
        prev_sum = new_sum;
        new_sum = 0;
        
        for (int16_t k = 0; k < SAMPLE_LEN - i; k++) {
            new_sum += ((audio_data[k] - 128)*(audio_data[k + i] - 128)) >> 8;
        }
  
        // Peak Detect State Machine
        if ((p_status_chk == 2) && (new_sum <= prev_sum)) {
            period = i;
            p_status_chk = 3;
        }
  
        if ((p_status_chk == 1) && (new_sum > thld) && (new_sum > prev_sum)) {
            p_status_chk = 2;
        }
  
        if (i == 0) {
            thld = new_sum >> 1;
            p_status_chk = 1;
        }
        
    }
  
    // Frequency identified in Hz
    if (thld > 100) {
        frequency = (int16_t)((float)SAMPLE_FREQ / (float)period + 0.5);
        // Call Note Display function
        
        return (uint16_t)frequency;
    }
  
    return 5;
}

void adc_end() {
    
    audio_data[curr_sample_index] = (uint8_t)ADRESH;  
    
    
    /*
    char freq[4];
    sprintf(freq, "%d", audio_data[curr_sample_index]);

    UARTPrint(freq);
    UARTPrint("\n\r");*/
    
    curr_sample_index++;

    if(curr_sample_index == SAMPLE_LEN - 1) {
        curr_sample_index= 0;
        display_print_int(get_frequency(audio_data));
        
    }
}