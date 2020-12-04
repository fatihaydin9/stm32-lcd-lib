#ifndef INC_LCD_CONFIG_H_
#define INC_LCD_CONFIG_H_

/* CONFIG FOR LIBRARY USER */
#define GPIO_PORT GPIOC

//4 pin mode -> pins
#define DATA_PIN1 GPIO_PIN_1
#define DATA_PIN2 GPIO_PIN_2
#define DATA_PIN3 GPIO_PIN_3
#define DATA_PIN4 GPIO_PIN_4

#define E_PIN  GPIO_PIN_5
#define RS_PIN GPIO_PIN_6
//RW Pin not used,connect to GND

//if 8-bit mode selected;
/*
#define LCD8Bit
#define DATA_PIN5 GPIO_PIN_5
#define DATA_PIN6 GPIO_PIN_6
#define DATA_PIN7 GPIO_PIN_7
#define DATA_PIN8 GPIO_PIN_8
*/

/******** CONFIG ENDS HERE *********/


#endif /* INC_LCD_CONFIG_H_ */
