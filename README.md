# STM32-LCD-Library
16x2 LCD Library - Compatible with All STM32 Boards

## LCD (16x2) Library v1 For STM32
**Compatible with All STM32 Boards**

This library provides to using STM32 and LCD together. This library debugged and tested on Nucleo F303RE Board. So if your device is different, you should be change header files which is used by your STM32 MCU.

#### Installing The LCD Library
Select port and pins which is suitable for your device. Then, you can configure part of code in lcd.h which is given below;

```c
/* CONFIG FOR LIBRARY USER */
#define GPIO_PORT GPIOC

#define DATA_PIN1 GPIO_PIN_1
#define DATA_PIN2 GPIO_PIN_2
#define DATA_PIN3 GPIO_PIN_3
#define DATA_PIN4 GPIO_PIN_4

#define E_PIN  GPIO_PIN_5
#define RS_PIN GPIO_PIN_6

```

#### Example
main.c file has an example for test your library works correct or not.

All the best,
Fatih.
