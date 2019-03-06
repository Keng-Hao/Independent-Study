 
#include<xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pic18f4520.h>
#include "delay.h"
#include "defines.h"
#include "initial.h"
#include "flex.h"
#include "UART.h"


#ifdef DEBUG
#include "lcd.h"
#endif
//#pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1H
//???????????????
/*
 * File:   LED.c
 * Author: user
 *
 * Created on 2016????4?? ??? 10:44
 */

// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements



// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTBE  // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected) 
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)
extern char test[15];
extern int test_index;
extern struct  STRUCT_USARTx_Fram                                  //??wifi??????????
{
    char  Data_RX_BUF [RX_BUF_MAX_LEN];         //RX_BUF_MAX_LEN

  union {
    u16 InfAll;
    struct {
          u8 FramLength       :7;                                    // 6:0 
          u8 FramFinishFlag   :1;                                   // 7 
      } InfBit;
  }; 

} strPc_Fram_Record, strEsp8266_Fram_Record;


extern struct  STRUCT_USART1_1_Fram                                   //??wifi??????????
{
    char  Data_RX_BUF [RX_BUF_MAX_LEN];            //RX_BUF_MAX_LEN

  union {
    u8 InfAll;
    struct {
          u8 FramLength       :7 ;                                   // 6:0 
          u8 FramFinishFlag   :1 ;                                   // 7 
      } InfBit;
  }; 
} strPc1_1_Fram_Record, str1_1esp8266;
u8 H,L,H_max,L_max,bounce_time,count,time,AD_L,AD_H,write;

void interrupt UART (void){
    if( INTCONbits.TMR0IF )
    {
        if(!write)
            ADCON0bits.GO=1;
        INTCONbits.TMR0IF=0;
    }
    if(PIR1bits.RCIF){
        char ch;
        ch  = RCREG;
        if( strEsp8266_Fram_Record .InfBit .FramLength < ( RX_BUF_MAX_LEN - 1 ) ) {  //??1???????
            strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ++ ]  = ch;
            if(strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength] == '\0')
                strEsp8266_Fram_Record .InfBit .FramFinishFlag = 1;
        }
        PIR1bits.RCIF=0;
//        if ( USART_GetITStatus( USART2, USART_IT_IDLE ) == SET )    
//            strEsp8266_Fram_Record .InfBit .FramFinishFlag = 1;
//            ch =RCREG;  
     
    }
    if(PIR1bits.ADIF){
       PIR1bits.ADIF=0; 
       AD_L=ADRESL;
       AD_H=ADRESH;
       write=1;
    }
}
//int test_index;
/*static*/unsigned char write,AD_L,AD_H;
void main(void)
{
    oclillator_initial();     
    GPIO_initial();
    initial_UART();
    ESP8266_Server();    
    while( ! (u8)strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "0,CONNECT" ));
    adc_initial();
    timer_0_initial();
    timer_intrrupt_initinal();
//    TRISDbits.RD1=1;
//    while(!PORTDbits.RD1);
    u16 AD_total;
    u8 temp[11];
    u8 tem[11];
    ADCON0bits.CHS=0;
//    TRISCbits.TRISC5=0;
//    LATCbits.LATC5=1;
    write=0;
#ifdef DEBUG
    LCD_Initialize();  
    LCD_Clear(); 
    LCD_GotoXY(0,0);
    LCD_WritetStr("Hello");
    delay_ms ( 3000 );
    LCD_Clear();
#endif
    while(1){

        ADCON0bits.CHS=(ADCON0bits.CHS+1)%10;
        while(!write);
        AD_total=AD_H;
        tem[ADCON0bits.CHS+1]=translate_flex(AD_total);
        if(ADCON0bits.CHS==0){
            tem[0]='!';
            ESP8266_SendString(0,tem,12);
            LATCbits.LATC5=!LATCbits.LATC5;
        }
        write=0;
//        detect_connect();
            

    }
}