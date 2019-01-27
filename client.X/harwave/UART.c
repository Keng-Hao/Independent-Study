#include <xc.h> 
#include "UART.h"
#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "delay.h"
//char test[10];
//int test_index;
struct  STRUCT_USARTx_Fram                                  //??wifi??????????
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


struct  STRUCT_USART1_1_Fram                                   //??wifi??????????
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
void initial_UART(){                                             //115200 baud rate ???
    TXSTAbits.SYNC=0;      //Asynchronous mode
    TXSTAbits.TX9=0;       //8-bit transmission
    RCSTAbits.SPEN=1;      //Serial Port Enable bit
    PIE1bits.TX1IE=0;      //turn off TX interrupt
    TXSTAbits.TXEN=1;         //enable the transmission  TXIF=1->TXREG register is empty
    
    INTCONbits.GIE=1;                   // Peripheral Interrupt disEnable bit
    INTCONbits.PEIE=1;                  // Global Interrupt Enable bit
    RCSTAbits.CREN=1;
    PIE1bits.RCIE=1;       //enable RX interrupt
    RCSTAbits.RC9 = 0;     //8-bit reception
    TXSTAbits.BRGH=1;      //High speed Baud Rate
    BAUDCONbits.BRG16=1;
    SPBRGH=0;
    SPBRG=86;
}
void ESP8266_Uart(char* cmd){                                   //transmit cmd
    int index=-1;
    do
    {
        index++;
        while(!TXIF);         //waitting for TXREG = empty
        TXREG=cmd[index];
    }while(cmd[index]!='\0');
    while(!TRMT);
}
u8 ESP8266_Cmd ( char* cmd , char* reply1 , char* reply2 ,u16 waittime )              // ESP8266 command instruction
    {    
        strEsp8266_Fram_Record .InfBit .FramLength = 0;               //???????????
//        test_index=0;
        ESP8266_Uart (cmd);
        
        if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //???????
            return true;

        delay_ms ( waittime );                 //????????????

        if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
            return ( (u8) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply1 ) || (u8) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply2 ) ); 
        else if ( reply1 != 0 )
            return ( (u8) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply1 ) );

        else
            return ( (u8) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply2 ) );


    }   
 u8 ESP8266_SendString ( u8 ucId ,char* pStr, u16 ulStrLength)  // ucId ????   send String 
{
    char cStr [20]={0};
    int bRet = false;
    char tem[12];
    
    
    strcpy(tem,pStr);
    tem[11]='\0';
    sprintf ( cStr,"AT+CIPSEND=%d,%d\r\n", ucId, ulStrLength);
    ESP8266_Cmd ( cStr,(void*)"> ",0, 30 ) ;
    bRet = ESP8266_Cmd ( tem, (void*)"SEND OK", 0, 30 );

    return bRet;

}
 void ESP8266_AT_Test ( void )          //AT??
{


    while ( !ESP8266_Cmd ( (void*)"AT\r\n",(void*) "OK", 0, 500 ) ) ;     

}
 void ESP8266_Rst ( void )            //AT reset
{
    #if 1
     ESP8266_Cmd ( (void*)"AT+RST\r\n", (void*)"OK",(void*) "ready", 6000 );     

    #else
     ESP8266_RST_LOW_LEVEL();
     Delay_ms ( 500 ); 
     ESP8266_RST_HIGH_LEVEL();

    #endif

}
u8 ESP8266_Net_Mode_Choose ( enum MODE MODE )   // STA AP STA/AP
{
    
    switch ( MODE )
    {
        case STA:
            return ESP8266_Cmd ( (void*)"AT+CWMODE=1\r\n", (void*)"OK", (void*)"no change", 2500 ); 

        case AP:
          return ESP8266_Cmd ( (void*)"AT+CWMODE=2\r\n",(void*) "OK", (void*)"no change", 2500 ); 

        case STA_AP:
          return ESP8266_Cmd ( (void*)"AT+CWMODE=3\r\n", (void*)"OK", (void*)"no change", 2500 ); 

      default:
          return false;
  }

}
u8 ESP8266_JoinAP ( char* pSSID, char* pPassWord )             // to connect AP
{
    char cCmd [120];
 
    sprintf ( cCmd, (void*)"AT+CWJAP=\"%s\",\"%s\"\r\n", pSSID, pPassWord );

    return ESP8266_Cmd ( cCmd, (void*)"OK", NULL, 7000 );

}
u8 ESP8266_BuildAP ( char* pSSID, char* pPassWord, char* enunPsdMode )        //pSSID name of AP pPassWord possword of AP enunPsdMode  method of encrypt   //channel =1 (default))
{
    char cCmd [120];

    sprintf ( cCmd, (void*)"AT+CWSAP=\"%s\",\"%s\",1,%s\r\n", pSSID, pPassWord, enunPsdMode );

    return ESP8266_Cmd ( cCmd, (void*)"OK", 0, 1000 );

}
u8 ESP8266_Link_Server ( enum TT enumE, char* ip, char* ComNum, int id) //id:0 is able to client/server contact?the other id only for server  //enumE?TCP?/?UDP?//  ip server IP address   //ComNum port number
{
    char cStr [100] = { 0 }, cCmd [120];

  switch (  enumE )
  {
        case TCP:
          sprintf ( cStr,(void*) "\"%s\",\"%s\",%s\r\n", "TCP", ip, ComNum );
          break;

        case UDP:
          sprintf ( cStr,(void*) "\"%s\",\"%s\",%s\r\n", "UDP", ip, ComNum );
          break;

        default:
            break;
  }

  if ( id < 5 ) //CIPMUX=1
    sprintf ( cCmd,(void*) "AT+CIPSTART=%d,%s\r\n", id, cStr);

  else  //CIPMUX=0
      sprintf ( cCmd,(void*) "AT+CIPSTART=%s\r\n", cStr );

    return ESP8266_Cmd ( cCmd, (void*)"CONNECT", (void*)"OK", 3000 );

}
void AP_MODE(){
    ESP8266_Net_Mode_Choose ( AP ) ;
    while(!ESP8266_Cmd ((void*) "AT+CWMODE?\r\n", (void*)"+CWMODE:2" , (void*)"OK" ,100));
}
void STA_MODE(){
    ESP8266_Net_Mode_Choose ( STA ) ;
    while(!ESP8266_Cmd ((void*) "AT+CWMODE?\r\n", (void*)"+CWMODE:1" , (void*)"OK" ,100));
}
 void ESP8266_Server(){
    ESP8266_AT_Test () ; 
    ESP8266_Rst (  );
    AP_MODE();
    while(!ESP8266_BuildAP ( (void *)"KEN", (void *)"zx4522331", (void *)"4")); 
    while(!ESP8266_Cmd ( (void *)"AT+CIPMUX=0\r\n",(void *) "OK", 0 , 500 ));
    while(!ESP8266_Cmd ( (void *)"AT+CIPMODE=0\r\n", (void *)"OK", 0 , 1000 ));
//    while(!ESP8266_Cmd ( "AT+CIPSERVER=0\r\n", "OK", 0 , 800 ));
    while(!ESP8266_Cmd ( (void *)"AT+CIPMUX=1\r\n", (void *)"OK", 0 , 500 ));
    while(!ESP8266_Cmd ( (void *)"AT+CIPSERVER=1,5000\r\n", (void *)"OK", 0 , 500 ));                //port location 5000
}
 void set_baudrate(enum Baudrate Baudrate){
     switch (Baudrate)
     {
        case B9600:
            while(!ESP8266_Cmd ( (void *)"AT+UART=9600,8,1,0,0\r\n", (void *)"OK", 0 , 500 ));
            break;
        case B115200:
            while(!ESP8266_Cmd ( (void *)"AT+UART=115200,8,1,0,0\r\n", (void *)"OK", 0 , 500 ));
            break;
        default:
            break;
     }
     
 }
 void detect_connect(void){
     if( (u8)strstr ( strEsp8266_Fram_Record .Data_RX_BUF, (void *)"0,CONNECT FAIL" ) ){
            while( ! (u8)strstr ( strEsp8266_Fram_Record .Data_RX_BUF, (void *)"0,CONNECT" ));
        }
 }
 void ESP8266_client(){
    ESP8266_AT_Test () ; 
    ESP8266_Rst ();
    ESP8266_Cmd ( (void *)"AT+CWQAP\r\n", (void *)"OK", 0 , 500 );
    STA_MODE();
    while(!ESP8266_JoinAP((void*)"Keng",(void*)"zx4522331"));
    while(!ESP8266_Cmd ( (void *)"AT+CIPMODE=1\r\n", (void *)"OK", 0 , 1000 ));
    while(!ESP8266_Cmd ( (void *)"AT+CIPMUX=0\r\n", (void *)"OK", 0 , 1000 ));
    while(!ESP8266_Link_Server(TCP,(void*)"192.168.4.1",(void*)"5000",7));     //最後一參數>5表示一對一模式AT+CIPMUX=0
    
 }