#include <xc.h>
#include <delays.h>
#include "delay.h"
void delay_ms(int ms)
{ 
    for(;ms>0;ms--)
    {
        Delay10KTCYx(1); 
    }
} 
#ifdef DEBUG
void delayFor18Tcy(void)
{
    Delay1TCYx(18);
}
#endif

