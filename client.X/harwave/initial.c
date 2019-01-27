#include"initial.h"

void GPIO_initial()
{

    TRISD = 0X00;
    PORTD = 0X00;
    LATD =0X00;
    TRISC = 0xF0;                 //keypad
}
void oclillator_initial()  //      Fosc = 40MHz 
{
    OSCCONbits.IOFS=0;        // turn off internal oscillator
    OSCCONbits.SCS0=0;
    OSCCONbits.SCS1=0;        //System Clock Select bits is primary oscillator
}
void timer_2_initial()                   //1m into interrupt
{
    PR2 = 200;
    T2CONbits.T2OUTPS=0b0000;            // 1:10 postscaler
    T2CONbits.T2CKPS=0b01;             // 1:4 prescaler
    T2CONbits.TMR2ON=0;                 // turn off timer2
}
void timer_0_initial()             //0.1 s in to interrupt percedure
{
    
    T0CONbits.T08BIT=1;       // 1 is 8 bits    0 is 16bits
    T0CONbits.T0CS=0;         // choose on timer
    T0CONbits.PSA=0;          // Timer0 prescaler is assigned
    T0CONbits.T0PS2=1;        // prescaler 1:16
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS0=1;
    T0CONbits.TMR0ON=1;       // turn on the timer0
}
void timer_intrrupt_initinal()
{
    RCONbits.IPEN=1;                    // turn off priority level
    INTCONbits.GIE=1;                   // Peripheral Interrupt disEnable bit
    INTCONbits.PEIE=1;                  // Global Interrupt Enable bit
    INTCONbits.TMR0IE=1;                // Enables the TMR0 overflow interrupt   
    INTCONbits.TMR0IF=0;                // Flag of Timer0
    PIE1bits.TMR2IE=0;                  // ENABLE?TMR2 interrupt bit
    PIR1bits.TMR2IF=0;                  // Flag if Timer2
}

void adc_initial(){
    ADCON0bits.ADON=1;                          //on adc
    ADCON1bits.VCFG1=0;                         //Vref = vss
    ADCON1bits.VCFG0=0;                         //Vref = vdd
    ADCON1bits.PCFG3=0;                         //AN0~AN9=analog other= digital
    ADCON1bits.PCFG2=1;
    ADCON1bits.PCFG1=0;
    ADCON1bits.PCFG0=1;
    ADCON0bits.CHS3=0;                          //channel an0
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS0=0;
    ADCON2bits.ADFM=0;                           //left justified
    ADCON2bits.ACQT2=1;                          // Tad=20Tad
    ADCON2bits.ACQT1=1;
    ADCON2bits.ACQT0=1;
    ADCON2bits.ADCS2=0;                          //adc clock ??? ???
    ADCON2bits.ADCS1=1;
    ADCON2bits.ADCS0=0;
    PIE1bits.ADIE=1;                             //adc interrupt
}