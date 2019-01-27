#ifndef _SOFTIIC_H
#define _SOFTIIC_H

#include "defines.h"

#define SDA_MODE TRISBbits.TRISB0
#define SCL_MODE TRISBbits.TRISB1

#define SDA_IN()  {SDA_MODE=1;} //SDA頛詨璅∪?
#define SDA_OUT() {SDA_MODE=0;}//SDA頛詨璅∪?

#define IIC_SCL    PORTBbits.RB1
#define IIC_SDA    PORTBbits.RB0 //SDA	 

#define READ_SDA   PORTBbits.RB0  //霈?DA 

//IIC???雿??
void IIC_Init(void);                //???IC?O??			 
void IIC_Start(void);				//?潮IC??靽∟?
void IIC_Stop(void);	  			//?潮IC?迫靽∟?
void IIC_Send_Byte(u8 txd);			//IIC?潮???蝭
u8 IIC_Read_Byte(unsigned char ack);//IIC霈????蝭
u8 IIC_Wait_Ack(void); 				//IIC蝑?ACK靽∟?
void IIC_Ack(void);					//IIC?潮CK靽∟?
void IIC_NAck(void);				//IIC銝?CK靽∟?

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	 

#endif