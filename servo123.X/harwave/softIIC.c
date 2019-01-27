    #include "softIIC.h"
#include "mydelay.h"

//IIC????
void IIC_Init(void)
{
    //SDA,SCL閮剔頛詨
    SCL_MODE  = 0;
    SDA_MODE  = 0;
    
    //IIC IDLE
    IIC_SCL = 1;
    IIC_SDA = 1;
}
//?Ｙ?IIC韏瑕?靽∟?
void IIC_Start(void)
{
	SDA_OUT();              //sda蝺撓??
	IIC_SDA=1;	  	                                                                                                                                
	IIC_SCL=1;                                                                                                                           
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//??I2C蝮賜?嚗?????交?豢? 
}	  
//?Ｙ?IIC?迫靽∟?
void IIC_Stop(void)
{
	SDA_OUT();//sda蝺撓??
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//?潮2C蝮賜?蝯?靽∟?
	delay_us(4);							   	
}
//蝑???靽∟??唬?
//餈??潘?1嚗?嗆?蝑仃??
//        0嚗?嗆?蝑???
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA閮剔蔭?箄撓?? 
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//??頛詨0 	   
	return 0;  
} 
//?Ｙ?ACK??
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//銝?CK??		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC?潮???蝭
//餈?敺????
//1嚗???
//0嚗??			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//???????豢??唾撓
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //撠EA5767???辣??臬???
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//霈1??蝭嚗ck=1???潮CK嚗ck=0嚗?ACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA閮剔蔭?箄撓??
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//?潮ACK
    else
        IIC_Ack(); //?潮CK   
    return receive;
}


























