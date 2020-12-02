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
    send4Bits(cmd >> 4);
    send4Bits(cmd);
}

void sendData(char data) {
    HAL_GPIO_WritePin(GPIO_PORT, RS_PIN, GPIO_PIN_SET);
    send4Bits(data >> 4);
    send4Bits(data);
}

void clearLCD(void) {
	sendCommand(LCD_CLEARDISPLAY);
	HAL_Delay(5);
}


void setCursorToFirstLine(void) {
    HAL_GPIO_WritePin(GPIO_PORT, RS_PIN, GPIO_PIN_RESET);
    sendCommand(0x80);
    HAL_Delay(2);
}

void setCursorToSecondLine(void) {
    HAL_GPIO_WritePin(GPIO_PORT, RS_PIN, GPIO_PIN_RESET);
    sendCommand(0x40);
    HAL_Delay(2);
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

	HAL_Delay(100); 	//Wait for more than 15 ms after VCC rises to 4.5 V

    send4Bits(0x03);
    HAL_Delay(10);
    send4Bits(0x03);
    send4Bits(0x03);
    send4Bits(0x02);

    sendCommand(0x20 | 0x08);
    sendCommand(0x08 | 0x04);
    sendCommand(0x01);
    HAL_Delay(1);
    sendCommand(0x04 | 0x02);
}




