/*
 *  lcd.h
 *
 *  Created on: Dec 1, 2020
 *  Author: fatay
 *
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f3xx_hal.h"
#include "lcd_config.h"



/* COMMANDS */

/* Command bit masks  */
#define LCD_CLEARDISPLAY    0x01
#define LCD_RETURNHOME      0x02
#define LCD_ENTRYMODESET    0x04
#define LCD_DISPLAYCONTROL  0x08
#define LCD_CURSORSHIFT     0x10
#define LCD_FUNCTIONSET     0x20
#define LCD_SETCGRAMADDR    0x40
#define LCD_SETDDRAMADDR    0x80

/* FunctionSet bits   */
#define LCD_8BITMODE     0x10
#define LCD_4BITMODE     0x00
#define LCD_2LINE        0x08
#define LCD_1LINE        0x00
#define LCD_5x10DOTS     0x04
#define LCD_5x8DOTS      0x00

/* Display control bits */
#define LCD_DISPLAYON 	 0x04
#define LCD_DISPLAYOFF	 0x00
#define LCD_CURSORON 	 0x02
#define LCD_CURSOROFF    0x00
#define LCD_BLINKON 	 0x01
#define LCD_BLINKOFF     0x00

/* Entry mode bits  */
#define LCD_ENTRYRIGHT 	 0x00
#define LCD_ENTRYLEFT 	 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00


void initLCD(void);
void clearLCD(void);
void setCursorToFirstLine(void);
void setCursorToSecondLine(void);
void putLCD(char c);
void writeLCD(char *str);
void setCursor(char x,char y);
void cursorOn(void);
void blinkOn(void);
#endif /* INC_LCD_H_ */
