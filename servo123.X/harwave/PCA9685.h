
#ifndef _PCA9685_H
#define	_PCA9685_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "defines.h"
#define PCA9685_SLAVE_ADDR 0x80    //PCA
#define prescale_address 0xFE 
#define PCA9685_fre 300
#define prescale_value 0x79       //set frequence 50hz for PAC9685
#define prescale_value_fre (25000000/4096/PCA9685_fre)-1
#define MODE1 0x00


void PCA9685_init(void);
void PCA9685_writeOneByte(u8 addr,u8 data);
u8 PCA9685_readOneByte(u16 addr);
void PCA9685_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);
void PCA9685_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);
#endif	/* XC_HEADER_TEMPLATE_H */

