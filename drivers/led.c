/*
 * led.c
 *
 *  Created on: June 25, 2020
 *      Author: Nguyen Cao Sang 1712933
 */

#include "led.h"

const   uint32_t    ledPin[3] = {GPIO_INT_PIN_1,GPIO_INT_PIN_2,GPIO_INT_PIN_3};

void    LedInit(void)
{
    // Enable GPIO Port F
    SysCtlPeripheralEnable(LED_GPIO_PERIPH);
    // Configure Pin 1,2,3 Port F as Output
    GPIOPinTypeGPIOOutput(LED_GPIO_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
}

void    LedControl(enum ledNumber led, enum ledState State)
{
    // Turn on/off LED
    if (State)  GPIOPinWrite(LED_GPIO_BASE,ledPin[led], ledPin[led]);
    else GPIOPinWrite(LED_GPIO_BASE,ledPin[led], 0);
}
