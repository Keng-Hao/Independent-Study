#include<xc.h>
#include "flex.h"
#include "defines.h"
#include "Table.h"
#include "PCA9685.h"
#include "mydelay.h"
void transmit_finger(u16 HL_Value ,u8 finger ){
    u8 Hbyte , Lbyte ;
    Lbyte = HL_Value ;
    Hbyte = HL_Value >> 8 ;
    PCA9685_writeOneByte(finger,0x00);   //300 servo
    PCA9685_writeOneByte(finger+1,0x00); 
    PCA9685_writeOneByte(finger+2,Lbyte);         //0x01FF
    PCA9685_writeOneByte(finger+3,Hbyte);
}
void ADtoPWM(u8* AD){
    u16 u0,u1,u2,u3,u4,w0,w1,w2,w3,w4;
//    w0=finger_under_0[*(AD+1)];
    if(*(AD+3)>=160)
        w1=finger_under_1[*(AD+3)-160];
    if(*(AD+5)>=143)
        w2=finger_under_2[*(AD+5)-143];
    if(*(AD+7)>=177)
        w3=finger_under_3[*(AD+7)-177];
    if(*(AD+9)>=136)
        w4=finger_under_4[*(AD+9)-136];
//    u0=finger_up_0[*AD];
    if(*(AD+2)>=138)
        u1=finger_up_1[*(AD+2)-138];
    if(*(AD+4)>=127)
        u2=finger_up_2[*(AD+4)-127];
    if(*(AD+6)>=110)
        u3=finger_up_3[*(AD+6)-110];
    if(*(AD+8)>=105)
        u4=finger_up_4[*(AD+8)-105];
//    PWMt0PCA(u0,w0,thumb);
    PWMt0PCA(u1,w1,index);
    PWMt0PCA(u2,w2,middle);
    PWMt0PCA(u3,w3,ring);
    PWMt0PCA(u4,w4,pink);
}

void PWMt0PCA(u16 up,u16 low,enum finger finger){
    switch (finger){
    case thumb:
        if( up > 0 )
            transmit_finger(up ,LED0_ON_L );
        else
            transmit_finger( up+low , LED0_ON_L );
        break;
    case index:
        if( up <= 1651 )
            transmit_finger(up ,LED1_ON_L );
        else
            transmit_finger( up+low , LED1_ON_L );
        break;
    case middle:
        if( up <= 2000 )
            transmit_finger(up ,LED2_ON_L );
        else
            transmit_finger( up+low , LED2_ON_L );
        break;
    case ring:
        if( up <= 1722 )
            transmit_finger(up ,LED3_ON_L );
        else
            transmit_finger( up+low , LED3_ON_L );
        break;
    case pink:
        if( up <= 1580 )
            transmit_finger(up ,LED4_ON_L );
        else
            transmit_finger( up+low , LED4_ON_L );
        break;
    }
}