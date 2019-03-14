
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
#endif	/* XC_HEADER_TEMPLATE_H */

