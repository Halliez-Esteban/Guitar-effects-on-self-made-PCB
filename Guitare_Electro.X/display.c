#include "config.h"
#include "functions.h"

 void display_init(){
    DISPLAY_CLK_TRIS = 0;   // Configurer CLK en sortie
    DISPLAY_DIO_TRIS = 0;   // Configurer DIO en sortie
    DISPLAY_CLK = 0;        // Mettre CLK à 0
    DISPLAY_DIO = 0;        // Mettre DIO à 0
    
    display_write_command(0x8A);
    display_print(0x0, 0x0, 0x0, 0x0, false);
}

 void display_start() {
    DISPLAY_DIO = 1;
    __delay_us(2);
    DISPLAY_CLK = 1;
    __delay_us(2);
    DISPLAY_DIO = 0;
    __delay_us(2);
    DISPLAY_CLK = 0;
    __delay_us(2);
}

void display_stop() {
    DISPLAY_DIO = 0;
    __delay_us(2);
    DISPLAY_CLK = 1;
    __delay_us(2);
    DISPLAY_DIO = 1;
    __delay_us(2);
}

void display_write_byte(unsigned char data) {
    for (unsigned char i = 0; i < 8; i++) {
        DISPLAY_CLK = 0;
        __delay_us(2);
        if (data & 0x01) {
            DISPLAY_DIO = 1;
        } else {
            DISPLAY_DIO = 0;
        }
        __delay_us(2);
        DISPLAY_CLK = 1;
        __delay_us(2);
        data >>= 1;
    }
    DISPLAY_CLK = 0;
    __delay_us(2);
    DISPLAY_DIO_TRIS = 1; // Configurer DIO en entrée pour lire l'accusé de réception
    __delay_us(2);
    DISPLAY_CLK = 1;
    __delay_us(2);
    
    //unsigned char ack = DISPLAY_DIO;
    
    __delay_us(2);
    DISPLAY_CLK = 0;
    __delay_us(2);
    DISPLAY_DIO_TRIS = 0; // Configurer DIO en sortie
    __delay_us(2);
}

void display_write_command(unsigned char cmd) {
    display_start();
    display_write_byte(cmd);
    display_stop();
}

void display_write_data(unsigned char addr, unsigned char data) {
    display_start();
    display_write_byte(0xC0 | addr); // Adresse de données du TM1637
    display_write_byte(data);
    display_stop();
}
 
void display_print(unsigned char data1,unsigned char data2,unsigned char data3,unsigned char data4, bool points){
    
    if(points)
        data2 = data2 | 0x80;
    else
        data2 = data2 & 0x7F;
    
    display_write_data(0x00, data1);
    display_write_data(0x01, data2);
    display_write_data(0x02, data3);
    display_write_data(0x03, data4);
    
    return;
    
}

void display_print_int(uint16_t intValue){
    
    unsigned char str[4]; 
    sprintf(str,"%d", intValue);
     
    unsigned char toPrint[4] = {0,0,0,0};
    
    for (unsigned int i = 0; i<4; i++){
        
        char number = str[i];
        
        switch(number){
            
            case '0': 
                toPrint[i]=CHAR_0;
                break;
            case '1': 
                toPrint[i]=CHAR_1;
                break;
            case '2': 
                toPrint[i]=CHAR_2;
                break;
            case '3': 
                toPrint[i]=CHAR_3;
                break;
            case '4': 
                toPrint[i]=CHAR_4;
                break;
            case '5': 
                toPrint[i]=CHAR_5;
                break;
            case '6': 
                toPrint[i]=CHAR_6;
                break;
            case '7': 
                toPrint[i]=CHAR_7;
                break;
            case '8': 
                toPrint[i]=CHAR_8;
                break;
            case '9': 
                toPrint[i]=CHAR_9;
                break;  
            default:
                toPrint[i]=0x0;
            
        }
        
    }
    
    display_print(toPrint[0],toPrint[1],toPrint[2],toPrint[3],false);
    
    
}

void display_clear() {
    display_print(0x0, 0x0, 0x0, 0x0, false);
}