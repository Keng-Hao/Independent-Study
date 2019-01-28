#ifndef MC24LC512_H
#define MC24LC512_H
// A0 A1 A2 => GND
#include "defines.h"
#define USE_HARDWAREIIC 0 //0使用軟件IIC，1使用硬件IIC
#define PCA9685_SLAVE_ADDR 0x80    //PCA
#define prescale_address 0xFE 
#define PCA9685_fre 267
#define prescale_value 0x79       //set frequence 50hz for PAC9685
#define prescale_value_fre (25000000/4096/PCA9685_fre)-1
#define MODE1 0x00
#define LED0_ON_L 0x06
#define LED1_ON_L 0x0A
#define LED2_ON_L 0x0E
#define LED3_ON_L 0x12  
#define LED4_ON_L 0x16
void PCA9685_init(void);
void PCA9685_writeOneByte(u8 addr,u8 data);
u8 PCA9685_readOneByte(u16 addr);
void PCA9685_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);
void PCA9685_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);
#endif