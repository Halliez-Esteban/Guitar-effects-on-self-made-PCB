#include "config.h"
#include "functions.h"


void UARTInit() {
    
    //PIE4bits.U1TXIE = 1;        // Enable interrupt
        
    U1CON0bits.TXEN = 1;        // Enable TX
    U1CON0bits.MODE = 0b0011;   // Set UART to Asynchronous 8-bit UART mode with 9th bit even parity
    U1CON0bits.ABDEN = 0;       
    U1CON0bits.BRGS = 1;
    
    U1CON2bits.TXPOL = 0;
    
    // Configure Baudrate for 115200
    U1BRGH = 0x00;
    U1BRGL = 0x10;              // BRG = 3 ? Baudrate ? 125000 (close to 115200)
    
    RC5PPS = 0x15;              // TX on RC5
    
    TRISCbits.TRISC5 = 0;       // Set RC5 as output
    
    U1CON1bits.ON = 1;          // Enable port
    
    UARTPrint("\n\r> UART Connection started!\n\n\r");

}


void UARTWriteByte(uint8_t data) {
    
    while (PIR4bits.U1TXIF == 0);           // wait for transmission idle

    U1TXB = data;
}

void UARTPrint(char msg[]) {
    
    for(uint8_t i = 0; i < strlen(msg); i++) {
        UARTWriteByte(msg[i]);
    }
    
    __delay_us(100);

}

void UARTPrintInt(uint16_t data) {
    
    char msg[10];
    
    sprintf(msg, "%d\n\r", data);
    
    UARTPrint(msg);
}