/*
 * Serial_Cal.h
 *
 *  Created on: Jul 11, 2020
 *      Author: LV_Embedded
 *      nguyenlamvien0110@gmail.com
 *      https://github.com/vien20010
 */

#ifndef MYLIB_SERIAL_CAL_H_
#define MYLIB_SERIAL_CAL_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "debug.h"

#define PI              3.14159265
#define msg1            " CALCULATOR PROGRAM"
#define msg2            " Enter First Number: "
#define msg3            " Enter Second Number: "
#define msg4            " Enter Operation: "
#define msg5            " Result = "

extern char check_uart;
extern int32_t num1 , num2;

char str[50];
char Operation;

char Result[50];


void Error_Notice(void);
void Check_Number(char *data);
void Check_Oper(char *data);
uint32_t Factorial(int32_t n);
bool Prime(int32_t n);
void Integer_Fac(int32_t n);
void Serial_Cal(void);
#endif /* MYLIB_SERIAL_CAL_H_ */
