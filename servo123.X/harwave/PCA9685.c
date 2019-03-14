#include "PCA9685.h"
#include "softIIC.h"
#include "mydelay.h"
#include "Table.h"
#include "flex.h"
void PCA9685_writeOneByte(u8 addr,u8 data)
{
    IIC_Start();
    IIC_Send_Byte(PCA9685_SLAVE_ADDR);
    IIC_Wait_Ack(); 
    IIC_Send_Byte(addr&0xff);
    IIC_Wait_Ack(); 
    IIC_Send_Byte(data);
    IIC_Wait_Ack(); 
    IIC_Stop();
    delay_ms(10);//???撖怠?撠?撱嗆?嚗wc = 5ms //??撱嗆??拙?
}