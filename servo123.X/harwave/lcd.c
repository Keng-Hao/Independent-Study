#include"lcd.h"
#include"mydelay.h"
#include "defines.h"
void LCD_Initialize()
{
    // clear latches before enabling TRIS bits
    LCD_PORT = 0;

    LCD_MODE = 0;
    delay_ms(LCD_Startup);
    
    LCD_WriteCmd(0X30);
    delay_ms(LCD_delay);
    
     LCD_WriteCmd(0X30);
    delay_ms(LCD_delay);
    
    LCD_WriteCmd(0x32);
   
    
    while(LCD_WaitBusy());
    LCD_WriteCmd(FUNCTION_SET);
    
    while(LCD_WaitBusy());
    LCD_WriteCmd(DOFF&CURSOR_OFF&BLINK_OFF);
    
    while(LCD_WaitBusy());
    LCD_WriteCmd(DON&CURSOR_OFF&BLINK_OFF);
  
    while(LCD_WaitBusy());
    LCD_Clear();

    // set cursor movement direction
    LCD_WriteCmd(ENTRY_MODE);
     
    while(LCD_WaitBusy());
    LCD_Clear();
}

//4bit 傳輸將8bit拆成兩半
void LCDWriteNibble(u8 ch,u8 rs)
{
    // always send the upper nibble
    ch = (ch >> 4);

    // mask off the nibble to be transmitted
    ch = (ch & 0x0F);
    #if UPPER
    // clear the high half of LCD_PORT
    LCD_PORT = (LCD_PORT & 0x0F);

    // move the nibble onto LCD_PORT
    LCD_PORT = (LCD_PORT | (ch << 4));
    #else
     // clear the low half of LCD_PORT
    LCD_PORT = (LCD_PORT & 0xF0);

    // move the nibble onto LCD_PORT
    LCD_PORT = (LCD_PORT | (ch ));
    #endif
    // set data/instr bit to 0 = insructions; 1 = data
    LCD_RS = rs;

    // RW - set write mode
    LCD_RW = 0;

    // set up enable before writing nibble
    LCD_EN = 1;

    // turn off enable after write of nibble
    LCD_EN = 0;
}

void LCD_WriteCmd(u8 ch)
{
    delay_ms(LCD_delay);

    //Send the higher nibble
    LCDWriteNibble(ch,LCD_CMD);

    //get the lower nibble
    ch = (ch << 4);

    delay_ms(1);

    //Now send the lower nibble
    LCDWriteNibble(ch,LCD_CMD);
}
void LCD_GotoXY(u8 pos,u8 ln)
{
    // if incorrect line or column
    if ((ln > (NB_LINES-1)) || (pos > (NB_COL-1)))
    {
        // Just do nothing
        return;
    }

    // LCD_Goto command
    LCD_WriteCmd((ln == 1) ? (0xC0 | pos) : (0x80 | pos));

    // Wait for the LCD to finish
    delay_ms(LCD_delay);
}

void LCD_WriteData(u8 ch)
{
    delay_ms(LCD_delay);

    //Send higher nibble first
    LCDWriteNibble(ch,LCD_DATA);

    //get the lower nibble
    ch = (ch << 4);

    // Now send the low nibble
    LCDWriteNibble(ch,LCD_DATA);
}

void LCD_WritetStr(const char *str)
{
    u8 i=0;
    
    // While string has not been fully traveresed
    while (str[i])
    {
        // Go display current char
        LCD_WriteData(str[i++]);
    }
    
}
/********************************************************************
*       Function Name:  LCD_WaitBusy                                    *
*       Return Value:   char: busy status of LCD controller         *
*       Parameters:     void                                        *
*       Description:    This routine reads the busy status of the   *
*                       Hitachi HD44780 LCD controller.             *
********************************************************************/
bool LCD_WaitBusy(void)
{
     LCD_RS = 0;
     LCD_RW = 1;
     delayFor18Tcy();
     LCD_EN = 1;
     delayFor18Tcy();
    #if UPPER
        LCD_MODE |= 0x80;
        if(LCD_PORT&0x80)
         {
                LCD_EN = 0;              // Reset clock line
                LCD_EN = 1;              // Clock out other nibble
                LCD_EN = 0;
                LCD_RW = 0;             // Reset control line
                LCD_MODE &=~(1<<7);
                return true;               // Return TRUE
        }
        else                            // Busy bit is low
        {
                LCD_EN = 0;              // Reset clock line
                LCD_EN = 1;              // Clock out other nibble
                LCD_EN = 0;
                LCD_RW = 0;             // Reset control line
                LCD_MODE &=~(1<<7);
                return false;               // Return FALSE
        }
    #else
         LCD_MODE |= 0x08;
         if(LCD_PORT&0x08)
          {
                LCD_EN = 0;              // Reset clock line
                LCD_EN = 1;              // Clock out other nibble
                LCD_EN = 0;
                LCD_RW = 0;             // Reset control line
                LCD_MODE &=~(1<<3);
                return true;               // Return TRUE
        }
        else                            // Busy bit is low
        {
                LCD_EN = 0;              // Reset clock line
                LCD_EN = 1;              // Clock out other nibble
                LCD_EN = 0;
                LCD_RW = 0;             // Reset control line
                LCD_MODE &=~(1<<3);
                return false;               // Return FALSE
        }
     #endif
       
}
void LCD_CreateFont(void)
{
    char byte[8]={0x1f,0x11,0x11,0x1f,0x11,0x11,0x1f,0x00};
    int i =0;
     LCD_SetCGRAM();
    for(;i<8;i++)
    {
        LCD_WriteData(byte[i]);
    }
     LCD_GotoXY(0,0);
     LCD_WriteData(0x00);
    
}