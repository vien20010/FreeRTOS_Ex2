/*
 * led.h
 *
 *  Created on: June 25, 2020
 *      Author: Nguyen Cao Sang 1712933
 */

#ifndef LED_H_
#define LED_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define LED_GPIO_PERIPH     SYSCTL_PERIPH_GPIOF
#define LED_GPIO_BASE       GPIO_PORTF_BASE

enum ledNumber {LEDRED = 0, LEDBLUE, LEDGREEN};
enum ledState  {OFF = 0, ON = 1};

void    LedInit(void);
void    LedControl(enum ledNumber led, enum ledState State);

#endif /* LED_H_ */
