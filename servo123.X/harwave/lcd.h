
#ifndef LCD_H
#define	LCD_H

#include <defines.h> // include processor files - each processor file is guarded.

/**
 Section: Macro Definitions
*/
// set up the timing for the LCD delays
#define LCD_delay           5     // ~5mS
#define LCD_Startup         15    // ~15mS

// Command set for Hitachi 44780U LCD display controller
#define LCD_CLEARDISP       0x01
#define LCD_HOME 
#define LCD_CGRAM 0X40
/* Display ON/OFF Control defines */
#define DON         0b00001111  /* Display on      */
#define DOFF        0b00001011  /* Display off     */
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */

// display controller setup commands from page 46 of Hitachi datasheet
#define FUNCTION_SET        0x28                         // 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE          0x06                         // increment mode
#define DISPLAY_SETUP       0x0C                         // display on, cursor off, blink offd


#define LCD_Clear()        LCD_WriteCmd(LCD_CLEARDISP)         // Legacy support
#define LCD_Home()         LCD_WriteCmd(LCD_HOME)
#define LCD_SetCGRAM()     LCD_WriteCmd(LCD_CGRAM)
//----------------------------------------------------------------------
// Definitions specific to the PICDEM 2 Plus
// These apply to the Black (2011) version.
//----------------------------------------------------------------------

// single bit for selecting command register or data register
#define LCD_CMD        0
#define LCD_DATA         1

// These #defines create the pin connections to the LCD in case they are changed on a future demo board
#define LCD_PORT     PORTD
#define LCD_MODE     TRISD
//D4 -> RB4
//D5 -> RB5
//D6 -> RB6
//D7 -> RB7
#define LCD_EN       PORTDbits.RD2                      // LCD enable
#define LCD_RW       PORTDbits.RD1                      // LCD read/write line
#define LCD_RS       PORTDbits.RD0                      // LCD register select line

#define NB_LINES 2
#define NB_COL  16
void LCD_Initialize();
void LCDWriteNibble(u8 ch,u8 rs);
void LCD_WriteCmd(u8 ch);
void LCD_GotoXY(u8 pos,u8 ln);
void LCD_WriteData(u8 ch);
void LCD_WritetStr(const char *str);
bool LCD_WaitBusy(void);
void LCD_CreateFont(void);
#endif