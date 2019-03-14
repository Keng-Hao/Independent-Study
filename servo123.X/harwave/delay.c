#include<delays.h>
#include"delay.h"
void delay_ms(int ms)
{ 
    for(ms=ms*25;ms>0;ms--)
    {
        Delay10TCYx(1);
    }
} 
void delay_us(int us)
{
    for(us=us*3;us>0;us--){
        Delay1TCYx(1);
    }
} 

