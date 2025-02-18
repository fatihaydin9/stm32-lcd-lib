/*
 *  lcd.h
 *
 *  Created on: Dec 1, 2020
 *  Author: fatay
 *
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "lcd_config.h"

#if defined(STM32F0)
#include "stm32f0xx_hal.h"
#elif defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#elif defined(STM32F3)
#include "stm32f3xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#else
#error "1602 library was tested only on STM32F0, STM32F1, STM32F3, STM32F4, STM32F7 MCU families."
#endif

/* COMMANDS */
#define LCD_CLEARDISPLAY    0x01
#define LCD_RETURNHOME      0x02
#define LCD_ENTRYMODESET    0x04
#define LCD_DISPLAYCONTROL  0x08
#define LCD_CURSORSHIFT     0x10
#define LCD_FUNCTIONSET     0x20
#define LCD_SETCGRAMADDR    0x40
#define LCD_SETDDRAMADDR    0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE  0x00
#define LCD_MOVERIGHT   0x04
#define LCD_MOVELEFT    0x00

// flags for function set
#define LCD_8BITMODE    0x10
#define LCD_4BITMODE    0x00
#define LCD_2LINE       0x08
#define LCD_1LINE       0x00
#define LCD_5x10DOTS    0x04
#define LCD_5x8DOTS     0x00

// ----- Flags for display/cursor/blink on/off control ----- //
typedef enum{
    LCD_DISPLAYON   = 0x04,
    LCD_DISPLAYOFF  = 0x00,
    LCD_CURSORON    = 0x02,
    LCD_CURSOROFF   = 0x00,
    LCD_BLINKON     = 0x01,
    LCD_BLINKOFF    = 0x00
}lcdDispSetting_t;

// ===== Functions ===== //
void initLCD(void);
void clearLCD(void);
void putLCD(char c);
void writeLCD(char *str);
void setCursor(char x,char y);
void cursorOn(void);
void blinkOn(void);

/**
  * @brief Clears the cursor and the blink bits.
  */
void clearDisp(void);

/**
  * @brief To set or reset the display/cursor/blink bits.
  * @param dispSetting Use or(|) operation to set multiple bit.
  */
void setDisplay(lcdDispSetting_t dispSetting);

#endif /* INC_LCD_H_ */