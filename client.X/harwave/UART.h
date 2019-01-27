
#ifndef UART_H
#define	UART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "defines.h"
#define RX_BUF_MAX_LEN 50
typedef enum TT  {
    TCP,
    UDP    
}TT;
typedef enum MODE {
    STA,
    AP,
    STA_AP
}MODE;
typedef enum Baudrate {
    B9600,
    B115200,
}Baudrate;
void initial_UART();
void ESP8266_Uart(char* cmd);
u8 ESP8266_Cmd( char* cmd , char* reply1 , char* reply2 , u16 waittime );

u8 ESP8266_SendString (u8 ucId , char* pStr , u16 ulStrLength);

void ESP8266_AT_Test ( void ) ;
void ESP8266_Rst ( void )  ;
u8 ESP8266_Net_Mode_Choose ( enum MODE MODE ) ;
u8 ESP8266_JoinAP ( char* pSSID, char* pPassWord );
u8 ESP8266_BuildAP ( char* pSSID, char* pPassWord, char* enunPsdMode );
u8 ESP8266_Link_Server ( enum TT enumE, char* ip, char* ComNum, int id);
void AP_MODE(void);
void ESP8266_Server(void);
void set_baudrate(enum Baudrate Baudrate);
void detect_connect(void);
void ESP8266_client();
void STA_MODE();

#endif	/* XC_HEADER_TEMPLATE_H */

