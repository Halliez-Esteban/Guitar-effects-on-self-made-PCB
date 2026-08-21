#include "config.h"
#include "functions.h"

void init_encoder() {
    
    init_btn_volume();
    init_encoder_volume();

    init_btn_fx();
    init_encoder_fx();
    
}


void init_btn_volume(){ 
    // initialiser un interrupt on change, falling edge pour le bouton centrale
    VOL_BUTTON_DIR = _ON;
    // PIN A3 en entré numérique
    ANSELAbits.ANSELA3 = _OFF;
    // Flag A3 à 0
    IOCAFbits.IOCAF3 = _OFF;
    // activer IOC falling du pin A3
    IOCANbits.IOCAN3 = _ON;
    //Désactiver le mute
    MUTE_PGA = _OFF;
    
};

void init_encoder_volume(){
    // initialiser B en entrée
    VOL_ENC_B_DIR = _ON;
    // PIN A2 en entré numérique
    ANSELAbits.ANSELA1 = _OFF;
    // initialiser un interrupt on change, falling edge pour A
    VOL_ENC_A_DIR = _ON;
    // PIN A4 en entré numérique
    ANSELAbits.ANSELA2 = _OFF;
    // Flag A4 à 0
    IOCAFbits.IOCAF2 = _OFF;
    // activer IOC falling du pin A3
    IOCANbits.IOCAN2 = _ON;
}

void init_btn_fx(){ 
    // initialiser un interrupt on change, falling edge pour le bouton centrale
    FX_BUTTON_DIR = _ON;
    // PIN A3 en entré numérique
    ANSELAbits.ANSELA4 = _OFF;
    // Flag A3 à 0
    IOCAFbits.IOCAF4 = _OFF;
    // activer IOC falling du pin A3
    IOCANbits.IOCAN4 = _ON;
    
};

void init_encoder_fx(){
    // initialiser B en entrée
    FX_ENC_B_DIR = _ON;
    // PIN A2 en entré numérique
    ANSELEbits.ANSELE0 = _OFF;
    // initialiser un interrupt on change, falling edge pour A
    FX_ENC_A_DIR = _ON;
    // PIN A4 en entré numérique
    ANSELAbits.ANSELA5 = _OFF;
    // Flag A4 à 0
    IOCAFbits.IOCAF5 = _OFF;
    // activer IOC falling du pin A4
    IOCANbits.IOCAN5 = _ON;
}

void vol_encoder_press(){
    
    MUTE_PGA = !MUTE_PGA;
    return;
    
}

void fx_encoder_press(){
    
    
    
}

void fx_encoder_rotating(int * COUNT2,int * current_fx){
  
  if(FX_READ_PORT == 1)
  {         // rotation sens Horaire
      COUNT2 ++;
      if(COUNT2 > FX_ENC_SEUIL) fx_increase(COUNT2, current_fx);
  }  
  else
  {         // rotation sens Horaire
      COUNT2 --;
      if(COUNT2 < (-FX_ENC_SEUIL)) fx_decrease(COUNT2, current_fx);
  }
  send_fx_choice(*current_fx);
  
  return;
}

void send_fx_choice(int current_fx){
    
    PROG0 = (current_fx % 2);
    PROG1 = ((current_fx>>1)%2);
    PROG2 = ((current_fx>>2)%2);
    PROG3 = ((current_fx>>3)%2);
    
}

void vol_encoder_rotating(int * COUNT,int * current_volume){
  
  if(VOL_READ_PORT == 1)
  {         // rotation sens Horaire
      *COUNT ++;
      if(*COUNT > VOL_ENC_SEUIL) vol_increase(COUNT, current_volume);
  }  
  else
  {         // rotation sens Horaire
      *COUNT--;
      if(*COUNT < (-VOL_ENC_SEUIL)) vol_decrease(COUNT, current_volume);
  }
  return;
}

void vol_decrease(int * COUNT,int * current_volume){
    
    // decrease volume with PGA
    *COUNT = 0;
    if(*current_volume>0)*current_volume--;
    
    return;
}

void vol_increase(int * COUNT,int * current_volume){
    
    // increase volume with PGA
    *COUNT = 0;
    if(*current_volume<volume_max)*current_volume++;
    
    return;
}

void fx_decrease(int * COUNT,int * current_fx){
    
    // Change effect
    *COUNT = 0;
    if(*current_fx>0)*current_fx--;
    else *current_fx=15;
    
    return;
}

unsigned char* get_current_value_into_string(int value){
    
    unsigned char str[2]; 
    sprintf(str,"%d", value);
     
    unsigned char toPrint[2];
    
    for (unsigned int i = 0; i<2; i++){
        
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
    return toPrint;
    
}

void fx_increase(int * COUNT, int * current_fx){
    
    // Change effect
    
    *COUNT = 0;
    *current_fx = (*current_fx+1)%program_count;
    display_print_int(*current_fx);
    
    return;
}
