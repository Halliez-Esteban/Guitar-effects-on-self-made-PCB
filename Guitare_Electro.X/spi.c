#include "config.h"
#include "functions.h"

void SPIInit() {
    
    /* Pin configuration */
    
    // Define SPI Data in on RB5
    SPI2SDIPPSbits.PORT = 0b001;
    SPI2SDIPPSbits.PIN  = 0b101;
    TRISBbits.TRISB5 = 1;        // Set as input
    
    // Define SPI Data out on RB2
    RB2PPSbits.RB2PPS2  = 0x21;
    TRISBbits.TRISB2 = 0;        // Set as output
    
    // Define SPI Clock out on RB1
    RB1PPS = 0x20;
    TRISBbits.TRISB1 = 0;        // Set as output
    
    // Define SPI Slave select out on RB3
    RB1PPS = 0x1F;
    TRISBbits.TRISB3 = 0;        // Set as output
    
    
    /* SPI configuration */
    
    SPI2CON0bits.LSBF   = 0;    // MSB first
    SPI2CON0bits.MST    = 1;    // PIC is master
    SPI2CON0bits.BMODE  = 0;    // default... not quite understood
    
    SPI2CON1bits.SMP    = 1;    // SDI enabling after emitting    
    SPI2CON1bits.CKE    = 0;    // Data transmission on rising clock edge
    SPI2CON1bits.CKP    = 0;    // Idle state = clock low 
    SPI2CON1bits.FST    = 0;    // Start clock afeter 1/2 baud period
    SPI2CON1bits.SSP    = 1;    // Client select is active on low
    SPI2CON1bits.SDIP   = 0;    // Input is on active high
    SPI2CON1bits.SDOP   = 0;    // Output is on active high
    
    SPI2CON2bits.SSET   = 0;    // Slave select disable only when transmit
    

    

    
    
    /* SPI Start */
    
    SPI2CON0bits.EN = 1;
}