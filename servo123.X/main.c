/*
 * File:   main.c
 * Author: user
 *
 * Created on 2017?4?19?, ?? 1:50
 */
#include<xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "replace.h"
#include "lcd.h"
#include "mydelay.h"
#include "defines.h"
#include "24lc512.h"
#include "softIIC.h"
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

volatile u16 base,pwm,x=0;
void GPIO_initial()
{
    TRISAbits.TRISA0=1;
    TRISAbits.TRISA1=0;
    TRISD = 0x00;
    LATD = 0x00;
    TRISC = 0xF0;
}
void oclillator_initial()  //      40MHz
{
    OSCCONbits.IOFS=0;        // turn off internal oscillator
    OSCCONbits.SCS0=0;
    OSCCONbits.SCS1=0;        //System Clock Select bits is internal oscillator
}
void PCA9685_init(){
    IIC_Init();
    PCA9685_writeOneByte(prescale_address,prescale_value);
    PCA9685_writeOneByte(MODE1,1);          //sleep =0
}
void timer_0_initial()
{
    T0CONbits.TMR0ON=0;       //close the timer0
    T0CONbits.T08BIT=1;       //8 bits
    T0CONbits.T0CS=0;         //choose on timer
    T0CONbits.PSA=0;          //Timer0 prescaler is assigned
    T0CONbits.T0PS2=0;        //prescaler 1:4
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS0=1;
}
void timer_intrrupt_initinal()
{
    RCONbits.IPEN=0;                    //turn off priority level
    INTCONbits.GIE=1;                   //Peripheral Interrupt Enable bit
    INTCONbits.PEIE=1;                  //Global Interrupt Enable bit
    INTCONbits.TMR0IE=1;                //Enables the TMR0 overflow interrupt   
    INTCONbits.TMR0IF=0;                //  ????????
}
void adc_initial(){
    ADCON0bits.ADON=1;                          //on adc
    ADCON1bits.VCFG1=0;                         //Vref = vss
    ADCON1bits.VCFG0=0;                         //Vref = vdd
    ADCON1bits.PCFG3=1;                         //AN0=analog other= digital
    ADCON1bits.PCFG2=1;
    ADCON1bits.PCFG1=1;
    ADCON1bits.PCFG0=0;
    ADCON0bits.CHS3=0;                          //channel an0
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS0=0;
    ADCON2bits.ADFM=1;                           //Right justified
    ADCON2bits.ACQT2=1;                          // Tad=20Tad
    ADCON2bits.ACQT1=1;
    ADCON2bits.ACQT0=1;
    ADCON2bits.ADCS2=0;                          //adc clock ??? ???
    ADCON2bits.ADCS1=0;
    ADCON2bits.ADCS0=1;
    PIE1bits.ADIE=0;                             //adc interrupt
}
//void interrupt ISR(void) {
//  if(INTCONbits.TMR0IF==1){
//      base++;
//      if(base==195){
//          LATAbits.LATA1=1;
//          base=0;
//          x=0;
//      }
//      x++;
//      if(x==pwm)
//         LATAbits.LATA1=0; 
//      INTCONbits.TMR0IF=0;
// } 
//}
void servo_U90degree()
{
    pwm=6;
}

void servo_90degree()
{
    pwm=31;
}
void servo_0degree()
{
    PCA9685_writeOneByte(0x06,0x99);
    PCA9685_writeOneByte(0x07,0x1);
    PCA9685_writeOneByte(0x08,0xCC);
    PCA9685_writeOneByte(0x09,0x4);
}
void scan_first_row()
{
     LATC=0xFE;
    if(PORTC==0xEE){                    //demonstrate F=+
      delay_ms(10);
      pwm++;
      delay_ms(200);
//      while(PORTC!=0xFE);
           delay_ms(10);
    }
    else if(PORTC==0xDE)                                //demonstrate E=-
        {
           delay_ms(10);
//           servo_90degree();
           pwm--;
          delay_ms(200);   
//           while(PORTC!=0xFE);
               delay_ms(10);
        }    
    else if(PORTC==0xBE)                               //demonstrate D=*
   {
           delay_ms(10); 
           servo_0degree();
           while(PORTC!=0xFE);
                delay_ms(10);
    }
    else if(PORTC==0x7E)                               //demonstrate C=/
        {
           delay_ms(10);
           servo_U90degree();
           while(PORTC!=0xFE);
                delay_ms(10);
        }
}
void main()
{
    oclillator_initial();     
    GPIO_initial();
    adc_initial();
    base=0;
    PCA9685_init();
    servo_0degree();
    timer_0_initial();
    timer_intrrupt_initinal();
    LCD_Initialize();
    int ADRES,ADRES1;
    float value;
    char temp[5];
    LCD_Clear();
    LCD_GotoXY(0,0);
    LCD_WritetStr("hello");
    while(1)
    {
//        scan_first_row();
//        ADCON0bits.GO=1;
//        if(PIR1bits.ADIF==1)
//        {
//            PIR1bits.ADIF=0;
//            ADRES=ADRESL;
//            ADRES1=ADRESH;
//            ADRES1=ADRES1*256;
//            value=(float)ADRES1+(float)ADRES;
//            value=value*0.0049;
//            sprintf(temp,"%1.2f v",value);
//            LCD_Clear();
//            LCD_GotoXY(0,0);
//            LCD_WritetStr(temp);
//            pwm=6+(25/value);
//        }
    }
}