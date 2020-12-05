/*
 * lcd.c
 *
 *  Created on: Dec 1, 2020
 *      Author: fatay
 */
#include <stdint.h>
#include "lcd.h"

#define SET_IF(expr)  ((expr) ? GPIO_PIN_SET : GPIO_PIN_RESET)
char display_settings;

//Sending falling edge signal to EPin for waking up LCD
static void fallingEdge(void) {
    HAL_GPIO_WritePin(GPIO_PORT, E_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIO_PORT, E_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIO_PORT, E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

#ifndef LCD8Bit
	static void send4Bits(char data) {
		HAL_GPIO_WritePin(GPIO_PORT, DATA5_Pin, SET_IF(data&0x01));
		HAL_GPIO_WritePin(GPIO_PORT, DATA6_Pin, SET_IF(data&0x02));
		HAL_GPIO_WritePin(GPIO_PORT, DATA7_Pin, SET_IF(data&0x04));
		HAL_GPIO_WritePin(GPIO_PORT, DATA8_Pin, SET_IF(data&0x08));

		fallingEdge();
	}
#endif

#ifdef LCD8Bit
	static void send8Bits(char val) {

		HAL_GPIO_WritePin(GPIO_PORT, DATA1_Pin, SET_IF(val&0x01));
		HAL_GPIO_WritePin(GPIO_PORT, DATA2_Pin, SET_IF(val&0x02));
		HAL_GPIO_WritePin(GPIO_PORT, DATA3_Pin, SET_IF(val&0x04));
		HAL_GPIO_WritePin(GPIO_PORT, DATA4_Pin, SET_IF(val&0x08));
		HAL_GPIO_WritePin(GPIO_PORT, DATA5_Pin, SET_IF(val&0x10));
		HAL_GPIO_WritePin(GPIO_PORT, DATA6_Pin, SET_IF(val&0x20));
		HAL_GPIO_WritePin(GPIO_PORT, DATA7_Pin, SET_IF(val&0x40));
		HAL_GPIO_WritePin(GPIO_PORT, DATA8_Pin, SET_IF(val&0x80));

		fallingEdge();
	}
#endif

static void sendCommand(char cmd) {
	#ifdef LCD8Bit
    	HAL_GPIO_WritePin(GPIO_PORT, RS_Pin, GPIO_PIN_RESET);
		send8Bits(cmd);
	#else
	    HAL_GPIO_WritePin(GPIO_PORT, RS_Pin, GPIO_PIN_RESET);
		send4Bits(cmd >> 4);
		send4Bits(cmd);
	#endif
}

static void sendData(char data) {
	#ifdef LCD8Bit
    	HAL_GPIO_WritePin(GPIO_PORT, RS_Pin, GPIO_PIN_SET);
		send8Bits(data);
	#else
	    HAL_GPIO_WritePin(GPIO_PORT, RS_Pin, GPIO_PIN_SET);
		send4Bits(data >> 4);
		send4Bits(data);
	#endif
}

void clearLCD(void) {
	sendCommand(LCD_CLEARDISPLAY);
	HAL_Delay(5);
}

void putLCD(char c) {
	sendData(c);
}

void writeLCD (char *str) {
	for(; *str != 0; ++str) {
		sendData(*str);
	}
}

void initLCD(void) {
    HAL_GPIO_WritePin(GPIO_PORT, E_Pin,  	 GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIO_PORT, RS_Pin, 	 GPIO_PIN_RESET);

	HAL_Delay(50);

	#ifdef LCD8Bit
		display_settings = LCD_8BITMODE | LCD_2LINE | LCD_5x8DOTS;
		sendCommand(LCD_FUNCTIONSET | display_settings);
		HAL_Delay(5);
		sendCommand(LCD_FUNCTIONSET | display_settings);
		HAL_Delay(5);
		sendCommand(LCD_FUNCTIONSET | display_settings);
		HAL_Delay(5);

	#else
		display_settings = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
		send4Bits(0x03);
		HAL_Delay(5);
		send4Bits(0x03);
		HAL_Delay(5);
		send4Bits(0x03);
		HAL_Delay(2);
		send4Bits(0x02);
		HAL_Delay(2);
	#endif
		sendCommand(LCD_FUNCTIONSET | display_settings);
		display_settings = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
		sendCommand(LCD_DISPLAYCONTROL | display_settings);
		HAL_Delay(2);

		clearLCD();
		display_settings =  LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
		sendCommand(LCD_ENTRYMODESET | display_settings);
		HAL_Delay(2);

}


void setCursor(char x, char y) {

	uint8_t base = 0;

	if(y==1) {
		base = 0x40;
	}else {
		base = 0;
	}

	sendCommand( 0x80 | (base + x));


}

void cursorOn(void) {
	sendCommand(0x08 | 0x04 | 0x02);
}

void blinkOn(void) {
	sendCommand(0x08 | 0x04 | 0x01);
}
