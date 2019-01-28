
#include "24lc512.h"
#include "i2c.h"
#include "softIIC.h"
#include "mydelay.h"


#if USE_HARDWAREIIC
#define WaitAck()  while(SSPCON2bits.ACKSTAT);
void PCA9685_init(void)
{
    OpenI2C(MASTER,SLEW_ON);//initialize I2C module
    SSPADD = 0X18;//400KHZ CLOCK
    IdleI2C();
}

void PCA9685_writeOneByte(u16 addr,u8 data)
{
    IdleI2C();
    StartI2C();
    WriteI2C(PCA9685_SLAVE_ADDR);
    WaitAck();
    WriteI2C((addr&0xff00)>>8);
    WaitAck();
    WriteI2C(addr&0xff);
    WaitAck();
    WriteI2C(data);
    WaitAck();
    StopI2C(); 
    delay_ms(10);
}
u8 PCA9685_readOneByte(u16 addr)
{
    u8 = 0;
    IdleI2C();
    StartI2C();
    WriteI2C(PCA9685_SLAVE_ADDR);
    WaitAck();
    WriteI2C((addr&0xff00)>>8);
    WaitAck();
    WriteI2C(addr&0xff);
    WaitAck();
    StartI2C();
    WriteI2C(PCA9685_SLAVE_ADDR+1);
    WaitAck(); 
    data = ReadI2C();
    NotAckI2C();
    StopI2C();
    return data;
}
#else
//24C512 敺??雿蔭撖思???蝭
//addr  :??雿蔭?啣?0~65535   
//data  :撖怠?豢?
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
//24C512 敺??雿蔭霈銝??蝭
//addr  :??雿蔭?啣?0~65535 
//餈?  :?豢?
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
//??4C512鋆⊿??摰???撖怠??????
//WriteAddr :??撖怠?? 撠?4c02??~255
//pBuffer   :?豢??貊?擐?
//NumToWrite:閬神?交???
void PCA9685_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		PCA9685_writeOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}

#endif