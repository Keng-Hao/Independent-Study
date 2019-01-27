
#ifndef FLEX_H
#define	FLEX_H

#include <xc.h>   
#include "defines.h"
#define Max_0_flex_up 0x08D1
#define Max_0_flex_down 0x0696
#define Min_0_flex_down 0x0387
#define Max_1_flex_up 0x09A5
#define Max_1_flex_down 0x05A5
#define Min_1_flex_down 0x0387
#define Max_2_flex_up 0x0B0F
#define Max_2_flex_down 0x062D
#define Min_2_flex_down 0x03A5
#define Max_3_flex_up 0x08E1
#define Max_3_flex_down 0x0596
#define Min_3_flex_down 0x032D
#define Max_4_flex_up 0x0B0F
#define Max_4_flex_down 0x06D2
#define Min_4_flex_down 0x0469
#define ADValue_up_0 0
#define ADValue_down_0 0
#define ADValue_up_1 135
#define ADValue_down_1 165
#define ADValue_up_2 124
#define ADValue_down_2 145
#define ADValue_up_3 101
#define ADValue_down_3 158
#define ADValue_up_4 110
#define ADValue_down_4 126
#define KALMAN_Q 0.02 
#define KALMAN_R 7.0000

double KalmanFilter_0(const double ResrcData_0,double ProcessNiose_Q_0,double MeasureNoise_R_0);
double KalmanFilter_1(const double ResrcData_1,double ProcessNiose_Q_1,double MeasureNoise_R_1);
double KalmanFilter_2(const double ResrcData_2,double ProcessNiose_Q_2,double MeasureNoise_R_2);
double KalmanFilter_3(const double ResrcData_3,double ProcessNiose_Q_3,double MeasureNoise_R_3);
double KalmanFilter_4(const double ResrcData_4,double ProcessNiose_Q_4,double MeasureNoise_R_4);
double KalmanFilter_5(const double ResrcData_5,double ProcessNiose_Q_5,double MeasureNoise_R_5);
double KalmanFilter_6(const double ResrcData_6,double ProcessNiose_Q_6,double MeasureNoise_R_6);
double KalmanFilter_7(const double ResrcData_7,double ProcessNiose_Q_7,double MeasureNoise_R_7);
double KalmanFilter_8(const double ResrcData_8,double ProcessNiose_Q_8,double MeasureNoise_R_8);
double KalmanFilter_9(const double ResrcData_9,double ProcessNiose_Q_9,double MeasureNoise_R_9);   
//u16 low_value (u16 AD_total_L,u16 a_value_L,u16 b_value_L,u16 Max_PCA_L) ;
//u16 high_value(u16 AD_total_H,u16 low,u16 a_value_H,u16 a_value1_H,u16 b_value_H,u16 low_pca_approximation);
//void transmit_finger(u16 HL_Value,u8 finger);
u8 translate_flex(u16 AD_total);

#endif	

