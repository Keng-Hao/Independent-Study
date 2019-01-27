#include <xc.h>
#include <delays.h>
#include"delay.h"
#include "mydelay.h"
void delay_ms1(int ms)
{
    do{
        Delay10KTCYx(1);    
        ms--;   
    }while(ms);
}

void delay_us1(int us)
{
    do{
        Delay10TCYx(1);
        us--;
    }while(us);
}
void delayFor18Tcy(void)
{
    Delay1TCYx(18);
}
