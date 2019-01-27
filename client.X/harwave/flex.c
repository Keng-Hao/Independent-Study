#include<xc.h>
#include "flex.h"
#include "defines.h"
#include "lcd.h"
//#include "24lc512.h"
#include <stdio.h>
#include <stdlib.h>
  double KalmanFilter_0(const double ResrcData_0,double ProcessNiose_Q_0,double MeasureNoise_R_0)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_0;
    double Q = ProcessNiose_Q_0;

    static double x_last_0;
    double x_mid = x_last_0;
    double x_now;

    static double p_last_0;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_0;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_0+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_0-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_0 = p_now;                     //??covariance ?
    x_last_0 = x_now;                     //???????
    return x_now;
}
    double KalmanFilter_1(const double ResrcData_1,double ProcessNiose_Q_1,double MeasureNoise_R_1)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_1;
    double Q = ProcessNiose_Q_1;

    static double x_last_1;
    double x_mid = x_last_1;
    double x_now;

    static double p_last_1;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_1;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_1+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_1-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_1 = p_now;                     //??covariance ?
    x_last_1 = x_now;                     //???????
    return x_now;
}
      double KalmanFilter_2(const double ResrcData_2,double ProcessNiose_Q_2,double MeasureNoise_R_2)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_2;
    double Q = ProcessNiose_Q_2;

    static double x_last_2;
    double x_mid = x_last_2;
    double x_now;

    static double p_last_2;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_2;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_2+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_2-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_2 = p_now;                     //??covariance ?
    x_last_2 = x_now;                     //???????
    return x_now;
}
        double KalmanFilter_3(const double ResrcData_3,double ProcessNiose_Q_3,double MeasureNoise_R_3)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_3;
    double Q = ProcessNiose_Q_3;

    static double x_last_3;
    double x_mid = x_last_3;
    double x_now;

    static double p_last_3;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_3;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_3+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_3-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_3 = p_now;                     //??covariance ?
    x_last_3 = x_now;                     //???????
    return x_now;
}
          double KalmanFilter_4(const double ResrcData_4,double ProcessNiose_Q_4,double MeasureNoise_R_4)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_4;
    double Q = ProcessNiose_Q_4;

    static double x_last_4;
    double x_mid = x_last_4;
    double x_now;

    static double p_last_4;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_4;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_4+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_4-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_4 = p_now;                     //??covariance ?
    x_last_4 = x_now;                     //???????
    return x_now;
}
  double KalmanFilter_5(const double ResrcData_5,double ProcessNiose_Q_5,double MeasureNoise_R_5)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_5;
    double Q = ProcessNiose_Q_5;

    static double x_last_5;
    double x_mid = x_last_5;
    double x_now;

    static double p_last_5;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_5;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_5+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_5-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_5= p_now;                     //??covariance ?
    x_last_5 = x_now;                     //???????
    return x_now;
}
    double KalmanFilter_6(const double ResrcData_6,double ProcessNiose_Q_6,double MeasureNoise_R_6)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_6;
    double Q = ProcessNiose_Q_6;

    static double x_last_6;
    double x_mid = x_last_6;
    double x_now;

    static double p_last_6;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_6;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_6+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_6-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_6 = p_now;                     //??covariance ?
    x_last_6 = x_now;                     //???????
    return x_now;
}
      double KalmanFilter_7(const double ResrcData_7,double ProcessNiose_Q_7,double MeasureNoise_R_7)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_7;
    double Q = ProcessNiose_Q_7;

    static double x_last_7;
    double x_mid = x_last_7;
    double x_now;

    static double p_last_7;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_7;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_7+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_7-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_7 = p_now;                     //??covariance ?
    x_last_7 = x_now;                     //???????
    return x_now;
}
        double KalmanFilter_8(const double ResrcData_8,double ProcessNiose_Q_8,double MeasureNoise_R_8)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_8;
    double Q = ProcessNiose_Q_8;

    static double x_last_8;
    double x_mid = x_last_8;
    double x_now;

    static double p_last_8;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_8;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_8+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_8-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_8 = p_now;                     //??covariance ?
    x_last_8 = x_now;                     //???????
    return x_now;
}
          double KalmanFilter_9(const double ResrcData_9,double ProcessNiose_Q_9,double MeasureNoise_R_9)          //because procedure , I change the static double to double
{

    double R = MeasureNoise_R_9;
    double Q = ProcessNiose_Q_9;

    static double x_last_9;
    double x_mid = x_last_9;
    double x_now;

    static double p_last_9;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last_9;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last_9+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??

    /*
     *  ????????????
     */
    kg=p_mid/(p_mid+R);                 //kg?kalman filter?R ???
    x_now=x_mid+kg*(ResrcData_9-x_mid);   //???????
    p_now=(1-kg)*p_mid;                 //??????covariance
    p_last_9 = p_now;                     //??covariance ?
    x_last_9 = x_now;                     //???????
    return x_now;
}     
          /*
u16 low_value( u16 AD_total_L , u16 a_value_L , u16 b_value_L,u16 Max_PCA_L ){                         //a_value = Max_300_up                 b_value = ADMin_300_up             
    u16 reture_value;
    char temp[5];
    if( ADCON0bits.CHS/2 == 0 ){
        AD_total_L=KalmanFilter_0((double)AD_total_L,1,1.5);
//        LCD_GotoXY(0,0);
//        sprintf(temp,"%.0f",(float)AD_total_L);
//        LCD_WritetStr(temp);
    }
    else if(ADCON0bits.CHS/2 == 1){
        AD_total_L=KalmanFilter_2((double)AD_total_L,1,1.5);
//        LCD_GotoXY(0,0);
//        sprintf(temp,"%.0f",(float)AD_total_L);
//        LCD_WritetStr(temp);
    }
    else if(ADCON0bits.CHS/2 == 2){
        AD_total_L=KalmanFilter_4((double)AD_total_L,1,1.5);
//        LCD_GotoXY(4,0);
//        sprintf(temp,"%.0f",(float)AD_total_L);
//        LCD_WritetStr(temp);
    }
    else if(ADCON0bits.CHS/2 == 3){
        AD_total_L=KalmanFilter_6((double)AD_total_L,1,1.5);
//        LCD_GotoXY(8,0);
//        sprintf(temp,"%.0f",(float)AD_total_L);
//        LCD_WritetStr(temp);
    }
    else if(ADCON0bits.CHS/2 == 4){
        AD_total_L=KalmanFilter_8((double)AD_total_L,1,1.5);
//        LCD_GotoXY(12,0);
//        sprintf(temp,"%.0f",(float)AD_total_L);
//        LCD_WritetStr(temp);
    }
    if(AD_total_L<= b_value_L )
        AD_total_L= b_value_L;
    reture_value= Max_PCA_L - (u16)( ( (float) (Max_PCA_L-a_value_L) / (float) (255-b_value_L) ) * (float)(AD_total_L-b_value_L) ) ;
    return reture_value;
}

u16 high_value( u16 AD_total_H , u16 low , u16 a_value_H ,u16 a_value1_H, u16 b_value_H,u16 low_pca_approximation ){         //a_value = Max_300_up                 b_value = ADMin_300_up
    u16 return_value;
    char temp[5];
//    if(low <= low_pca_approximation){
        if( ADCON0bits.CHS/2 == 0 )
            AD_total_H=KalmanFilter_1((double)AD_total_H,1,1.5);
        else if(ADCON0bits.CHS/2 == 1)
                  AD_total_H=KalmanFilter_3((double)AD_total_H,1,1.5);
        else if(ADCON0bits.CHS/2 == 2)
                  AD_total_H=KalmanFilter_5((double)AD_total_H,1,1.5);
        else if(ADCON0bits.CHS/2 == 3)
                  AD_total_H=KalmanFilter_7((double)AD_total_H,1,1.5);
        else if(ADCON0bits.CHS/2 == 4)
                  AD_total_H=KalmanFilter_9((double)AD_total_H,1,1.5);
        
        if(AD_total_H<= b_value_H )
            AD_total_H= b_value_H;
        return_value=low-(u16)(( (float)(a_value_H-a_value1_H) / (float)(255-b_value_H) ) * (float)(AD_total_H- b_value_H ) ) ;
//        return return_value;
//    }
//    else
//        return low;
    return return_value;

}

void transmit_finger(u16 HL_Value ,u8 finger ){
    u8 Hbyte , Lbyte ;
    Lbyte = HL_Value ;
    Hbyte = HL_Value >> 8 ;
    PCA9685_writeOneByte(finger,0x00);   //300 servo
    PCA9685_writeOneByte(finger+1,0x00); 
    PCA9685_writeOneByte(finger+2,Lbyte);         //0x01FF
    PCA9685_writeOneByte(finger+3,Hbyte);
}
*/
u8 translate_flex(u16 AD_total){
    u8 Value;
    u8 temp;
    u8 temp1[4];

    switch ( ADCON0bits.CHS / 2 ){
            case 0:
                if( !(ADCON0bits.CHS%2) ){
                    Value=(u8)KalmanFilter_0((double)AD_total,1,1.5);
                    temp=Value;
                }
                else{
                    Value=(u8)KalmanFilter_1((double)AD_total,1,1.5);
                    temp=Value;
                }
                break;
            case 1:
                if( !(ADCON0bits.CHS%2) ){
                    if(ADCON0bits.CHS== 2){
                        Value=(u8)KalmanFilter_2((double)AD_total,1,1.5);
                        temp=Value;
                    }
                }
                else{
                    Value=(u8)KalmanFilter_3((double)AD_total,1,1.5);
                    temp=Value;
                }
                break;
            case 2:
                if( !(ADCON0bits.CHS%2) ){
                    Value=(u8)KalmanFilter_4((double)AD_total,1,1.5);
                    temp=Value;
                }
                else{
                    Value=(u8)KalmanFilter_5((double)AD_total,1,1.5);
                    temp=Value;
                }
                break;
            case 3:
                if( !(ADCON0bits.CHS%2) ){
                    Value=(u8)KalmanFilter_6((double)AD_total,1,1.5);
                    temp=Value;
                }
                else{
                    Value=(u8)KalmanFilter_7((double)AD_total,1,1.5);
                    temp=Value;
                }
                break;
            case 4:
                if( !(ADCON0bits.CHS%2) ){
                    Value=(u8)KalmanFilter_8((double)AD_total,1,1.5);
                    temp=Value;
                }
                else{
                    Value=(u8)KalmanFilter_9((double)AD_total,1,1.5);
                    temp=Value;
                }
                break;
                default:
//                    LCD_WritetStr("Erro");
                    break;
                   
            }
    return temp;
}