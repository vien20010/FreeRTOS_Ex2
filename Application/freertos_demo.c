/*
 * freertos_demo.c
 *
 *  Created on: June 25, 2020
 *      Author: Nguyen Cao Sang 1712933
 */

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"

#include "drivers/led.h"
#include "drivers/switches.h"
#include "drivers/uartstdio.h"
#include "drivers/debug.h"
#include "drivers/Serial_Cal.h"
#include "drivers/LCD 8bit.h"


#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/semphr.h"

// The error routine that is called if the driver library encounters an error.
#ifdef DEBUG

void __error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

// format data for Queue
#define LEDGREENON 0
#define LEDYELLOWON 1
#define LEDREDON 2

//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************
/*static void RGBTask(void *pvParameters);
static void command1(void *pvParameters);
static void command2(void *pvParameters);
static void action(void *pvParameters);*/

static void LedRed(void *pvParameters);
static void LedBlue(void *pvParameters);

void UARTIntHandler(void);


xTaskHandle xTask2Handle;

// declare QueueHandle, SemaphoreHandle variables as global variables
xQueueHandle xQueue;
//xSemaphoreHandle xBinarySemaphore;

// Define the structure type that will be passed on the queue
typedef struct
{
    unsigned int ledValue;
} Data_t;

typedef enum {S_GREEN, S_YELLOW, S_RED} detect_t;
detect_t d = S_GREEN;
uint32_t t = 15000;

void vApplicationTickHook(void)
{
    if (t > 0)
    {
        t--;
        if(t%1000 == 0)
            UARTprintf("Tick count down: %d \n", t/1000);
    }
}

//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************
int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    InitConsole();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        //enable GPIO port for LED
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); //enable pin for LED PF2

    IntMasterEnable();                                    //enable processor interrupts
    IntEnable(INT_UART0);                                 //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts

    LedInit();
    switchInit();
    LedControl(LEDRED, OFF);
    LedControl(LEDBLUE, OFF);
    /*xQueue = xQueueCreate( 3, sizeof( Data_t ) );

    xTaskCreate(command1, "sendTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(command2, "sendTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(action, "receiveTask", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(RGBTask, "LEDTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);*/

    xTaskCreate(LedRed,"Red",240,NULL,1,NULL);
    xTaskCreate(LedBlue,"Blue",240,NULL,1,NULL);

    vTaskStartScheduler();
    while(1)
    {
    }
}

static void LedRed(void *pvParameters)
{
    while (1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
        DBG("Task 1\n");
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}
static void LedBlue(void *pvParameters)
{
    char count=0;
    //uint32_t preVal, currentVal;
    while (1)
    {
        if (!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
        {
            while (!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4));
            count++;
        }
        if (count==3)
        {
            DBG("Task 2\n");
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2));
            count=0;
        }
    }
}


void UARTIntHandler(void)
{
    char k;
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    UARTIntClear(UART0_BASE,UARTIntStatus(UART0_BASE,true));
    k = UARTgetc();
    if (k == '0')
    {
        t = 0;
    }
    else if (k == '5')
    {
        t += 5000;
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

/*static  void command1(void *pvParameters)
{
    for (;;)
    {
        if (switchState(1) == PRESSED)
        {
            vTaskDelay(100);
            if (switchState(1) == PRESSED)
            t = 0;
        }
        taskYIELD();
    }
}

static  void command2(void *pvParameters)
{
    for (;;)
    {
        if (switchState(2) == PRESSED)
        {
            vTaskDelay(100);
            if (switchState(2) == PRESSED)
            t += 5000;
        }
        taskYIELD();
    }
}

static void RGBTask(void *pvParameters)
{
    UARTprintf("Turn on GREEN LED \n");
    UARTprintf("Tick count down: %d \n", t/1000);
    Data_t  data;
    for (;;)
    {
        switch(d)
        {
        case S_GREEN:
            if (t == 0)
            {
                d = S_YELLOW;
                UARTprintf("Turn on YELLOW LED \n");
                t = 3000;
                UARTprintf("Tick count down: %d \n", t/1000);
            }
            break;
        case S_YELLOW:
            if (t == 0)
            {
                d = S_RED;
                UARTprintf("Turn on RED LED \n");
                t = 15000;
                UARTprintf("Tick count down: %d \n", t/1000);
            }
            break;
        case S_RED:
            if (t == 0)
            {
                d = S_GREEN;
                UARTprintf("Turn on GREEN LED \n");
                t = 15000;
                UARTprintf("Tick count down: %d \n", t/1000);
            }
            break;
        }

        switch(d)
        {
        case S_GREEN:
            data.ledValue = LEDGREENON;
            xQueueSend(xQueue, &data, portMAX_DELAY);
            break;
        case S_YELLOW:
            data.ledValue = LEDYELLOWON;
            xQueueSend(xQueue, &data, portMAX_DELAY);
            break;
        case S_RED:
            data.ledValue = LEDREDON;
            xQueueSend(xQueue, &data, portMAX_DELAY);
            break;
        }
    }
}

static void action(void *pvParameters)
{
    Data_t   data;
    for(;;)
    {
        xQueueReceive(xQueue, &data, portMAX_DELAY);

        if (data.ledValue == LEDGREENON)
        {
            LedControl(LEDGREEN, ON);
            LedControl(LEDRED, OFF);
        }
        else if (data.ledValue == LEDYELLOWON)
        {
            LedControl(LEDGREEN, ON);
            LedControl(LEDRED, ON);
        }
        else
        {
            LedControl(LEDGREEN, OFF);
            LedControl(LEDRED, ON);
        }
    }
}
*/
