## LCD (16x2) Library For STM32
**Compatible with All STM32 Boards**

This library provides to using STM32 and LCD together. This library debugged and tested on Nucleo F303RE and STM32F4 Discovery Boards. So if your device is different, you should be change header files which is used by your STM32 MCU Compiler.

### Installing The LCD Library
**4 Bit(Default) Mode Installation**
Select port and pins which is suitable for your device. Then, open lcd_config.h file with text editor.

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
**8 Bit Mode Installation**
If you want to 8 bit mode, you should be uncomment this area in "lcd_config.h" and then you can configure pins.
```c
//if 8-bit mode selected;

#define LCD8Bit
#define DATA_PIN5 GPIO_PIN_5
#define DATA_PIN6 GPIO_PIN_6
#define DATA_PIN7 GPIO_PIN_7
#define DATA_PIN8 GPIO_PIN_8

```

#### Example
main.c file has an example to test your library works correctly or not.
