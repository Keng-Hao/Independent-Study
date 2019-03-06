#include"initial.h"
#include "24lc512.h"
#include "i2c.h"
#include "softIIC.h"
void GPIO_initial()
{
    TRISD = 0x00;
    LATD = 0x00;
    TRISAbits.RA0=0;
    LATAbits.LA0=0;
//    TRISC = 0xF0;                 //keypad
}
void oclillator_initial()  //      Fosc = 40MHz 
{
    OSCCONbits.IOFS=0;        // turn off internal oscillator
    OSCCONbits.SCS0=0;
    OSCCONbits.SCS1=0;        //System Clock Select bits is primary oscillator
}
void PCA9685_init(){
    IIC_Init();
    PCA9685_writeOneByte(MODE1,0x11);
    PCA9685_writeOneByte(prescale_address,prescale_value_fre);          //300hz servo
    PCA9685_writeOneByte(MODE1,0x01);          //sleep =0
}
void timer_0_initial()             // s in to interrupt percedure
{
    
    T0CONbits.T08BIT=1;       // 1 is 8 bits    0 is 16bits
    T0CONbits.T0CS=0;         // choose on timer
    T0CONbits.PSA=0;          // Timer0 prescaler is assigned
    T0CONbits.T0PS2=1;        // prescaler 1:32
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS0=0;
    T0CONbits.TMR0ON=1;       // turn on the timer0
}
void timer_intrrupt_initinal()
{
    RCONbits.IPEN=1;                    // turn off priority level
    INTCONbits.GIE=1;                   // Peripheral Interrupt disEnable bit
    INTCONbits.PEIE=1;                  // Global Interrupt Enable bit
    INTCONbits.TMR0IE=0;                // Enables the TMR0 overflow interrupt   
    INTCONbits.TMR0IF=0;                // Flag of Timer0
    PIE1bits.TMR2IE=0;                  // ENABLE?TMR2 interrupt bit
    PIR1bits.TMR2IF=0;                  // Flag if Timer2
}
void timer_2_initial()                    //1m into interrupt
{
    PR2 = 249;
    T2CONbits.T2OUTPS=0b1001;            // 1:10 postscaler
    T2CONbits.T2CKPS=0b01;             // 1:4 prescaler
    T2CONbits.TMR2ON=0;                 // turn off timer2
}