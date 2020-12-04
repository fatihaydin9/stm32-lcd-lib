/*
 * lcd.c
 *
 *  Created on: Dec 1, 2020
 *      Author: fatay
 */


/*
 *
 * #define GPIO_PORT GPIOC
 * #define DATA_PIN1 1
 * #define DATA_PIN2 2
 * #define DATA_PIN3 3
 * #define DATA_PIN4 4
 *
 * #define E_PIN  5
 * #define RS_PIN 6
*/
#include "lcd.h"

//Sending falling edge signal to EPin for waking up LCD
static void fallingEdge(void) {
    HAL_GPIO_WritePin(GPIO_PORT, E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIO_PORT, E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

// sending 4 bits
static void send4Bits(char data) {
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN1, data & 0x01);
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN2, data & 0x02);
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN3, data & 0x04);
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN4, data & 0x08);

    fallingEdge();
}

static void sendCommand(char cmd) {
    HAL_GPIO_WritePin(GPIO_PORT, RS_PIN, GPIO_PIN_RESET);
	#if LCD8Bit
	send8Bits(cmd);
	#else
		send4Bits(cmd >> 4);
		send4Bits(cmd);
	#endif
}

void sendData(char data) {
    HAL_GPIO_WritePin(GPIO_PORT, RS_PIN, GPIO_PIN_SET);
	#if LCD8Bit
	send8Bits(data);
	#else
		send4Bits(data >> 4);
		send4Bits(data);
	#endif
}

void clearLCD(void) {
	sendCommand(LCD_CLEARDISPLAY);
	HAL_Delay(5);
}

void putLCD(char c) {
    HAL_GPIO_WritePin(GPIO_PORT, RS_PIN, GPIO_PIN_SET);
	sendData(c);
    HAL_GPIO_WritePin(GPIO_PORT, RS_PIN, GPIO_PIN_RESET);
}

void writeLCD (char *str) {
    HAL_GPIO_WritePin(GPIO_PORT, RS_PIN, GPIO_PIN_SET);
    while (*str != '\0') {
    	sendData((char) *str++);
    }
}

void initLCD(void) {

    HAL_GPIO_WritePin(GPIO_PORT, E_PIN,  GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIO_PORT, RS_PIN, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN1,  GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN2,  GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN3,  GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN4,  GPIO_PIN_RESET);

	#ifdef LCD8Bit
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN5,  GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN6,  GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN7,  GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIO_PORT, DATA_PIN8,  GPIO_PIN_RESET);
	#endif

	HAL_Delay(150);

    send4Bits(0x03);
    HAL_Delay(10);
    send4Bits(0x03);
    HAL_Delay(5);
    send4Bits(0x03);
    HAL_Delay(2);
    send4Bits(0x02);
    HAL_Delay(2);

    sendCommand(0x20 | 0x08);	//set parameters
    HAL_Delay(2);
    sendCommand(0x08 | 0x04);	//display on
    HAL_Delay(2);
    sendCommand(0x01);			//clear screen
    HAL_Delay(2);
    sendCommand(0x04 | 0x02);	//entry mode set
    //Entry mode command sets cursor move direction
    HAL_Delay(2);
}


void setCursor(char x, char y) {

	unsigned int base = 0;

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

