
#ifndef FLEX_H
#define	FLEX_H

#include <xc.h>   
#include "defines.h"
#define LED0_ON_L 0x06
#define LED1_ON_L 0x0A
#define LED2_ON_L 0x0E
#define LED3_ON_L 0x12  
#define LED4_ON_L 0x16
enum finger {
    thumb=0,
    index,
    middle,
    ring,
    pink
    
};
void ADtoPWM(u8* AD);
void PWMt0PCA(u16 up,u16 low,enum finger finger);
void transmit_finger(u16 HL_Value,u8 finger);
void translate_flex(u16 AD_total);

#endif	

