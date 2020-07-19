
#ifndef LCD_8BIT_H_
#define LCD_8BIT_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "driverlib/fpu.h"
#include "driverlib/ssi.h"

#include "drivers/led.h"
#include "drivers/switches.h"
#include "drivers/uartstdio.h"
#include "drivers/debug.h"
#include "drivers/LCD 8bit.h"

#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/semphr.h"

void lcd_init(void);
void lcd_command(char);
void lcd_char(char);
void lcd_string(char *);
void lcd_print (uint32_t value, int digits);
void lcd_cursor(char,char);


#endif /* LCD_8BIT_H_ */
