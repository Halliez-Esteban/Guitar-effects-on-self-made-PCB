#include "config.h"

/* GLOBAL */
void initialize(void);
void init_interrupts(void); // Normal and IOC


/* DISPLAY */
void display_init();
void display_start();
void display_stop();
void display_write_byte(unsigned char data);
void display_write_command(unsigned char cmd);
void display_write_data(unsigned char addr, unsigned char data);
void display_print(unsigned char data1,unsigned char data2,unsigned char data3,unsigned char data4, bool points);
void display_print_int(uint16_t intValue);
void display_clear();

unsigned char* get_current_value_into_string(int value);

/* TUNER */
void init_tuner();
void init_adc();
void init_tmr0();

void adc_end();
uint16_t get_frequency(uint8_t audio_data[]);



/* ENCODERS */
void init_encoder();
void initialiser_interrupt_on_change();

void init_btn_volume();
void init_encoder_volume();
void init_btn_fx();
void init_encoder_fx();

void vol_encoder_rotating(int * COUNT,int * current_volume);
void fx_encoder_rotating(int * COUNT2,int * current_fx);
void send_fx_choice(int current_fx);

void vol_encoder_press();
void fx_encoder_press();

void vol_increase(int * COUNT, int * current_volume);
void vol_decrease(int * COUNT, int * current_volume);
void fx_increase(int * COUNT2, int * current_fx);
void fx_decrease(int * COUNT2, int * current_fx);


/* UART */
void UARTInit();                            // init UART with specified baud rate
uint8_t UARTReadByte(void);                 // read a byte from UART
void UARTWriteByte(uint8_t data);           // write a byte to UART
void UARTPrint(char msg[]);
void UARTPrintInt(uint16_t data);


/* SPI */