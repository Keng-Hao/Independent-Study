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
u8 PCA9685_readOneByte(u16 addr)
{
    unsigned char data = 0;
    IIC_Start();
    IIC_Send_Byte(PCA9685_SLAVE_ADDR);//?????
//    IIC_Wait_Ack();
//    IIC_Send_Byte((addr&0xff00)>>8);//?????
    IIC_Wait_Ack();
    IIC_Send_Byte(addr&0xff);//?????
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte(PCA9685_SLAVE_ADDR+1);//??????	
    IIC_Wait_Ack(); 
    data = IIC_Read_Byte(0);//???byte????nack
    IIC_Stop();
    return data;
}
void PCA9685_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=PCA9685_readOneByte(ReadAddr++);	
		NumToRead--;
	}
}
void PCA9685_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		PCA9685_writeOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}

