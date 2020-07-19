    /**
 * Serial_Cal.h
 *
 *  Created on: Jul 11, 2020
 *      Author: LV_Embedded
 *      nguyenlamvien0110@gmail.com
 *      https://github.com/vien20010
 */

#include "Serial_Cal.h"


/** 
 * @brief - Stop Program when input is systax error and turn on led Blue to notice
 * @param - none
 * @retval - none
 */
void Error_Notice(void)
{
    DBG("Syntax Error -> Reset to Cal\n");
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //Turn on led BLue
    while (1) //Stop Program
    {
    }
}

/**
 * @brief - Check your input: if it isn't number, the Program Error_Notice will run
 * @param data - your input string want to check
 * @retval - none
 */
void Check_Number(char *data)
{
    uint16_t j;
    for (j = 0; *(data + j) != '\0'; j++)
    {
        /* Check each byte data if it isn't number */
        DBG("%c\n",*(data+j));
        if ((*(data + j) < '0') || (*(data + j) > '9')) 
            Error_Notice();
    }
}


/** 
 * @brief - check your operator
 * @param data - your input string operator want to check
 * @retval - none
 */
void Check_Oper(char *data)
{
    /* The condition is Operator is 1 byte so we check the next bye
     If it isn't exit byte --> Syntax Error*/
    if (*(data + 1) != '\0')
        Error_Notice();

    /* Check Operator */
    if (!((*data == '+') || (*data == 'r') || (*data == '-') || (*data == '*') || (*data == '/') || (*data == '^') || (*data == '!') || (*data == '?') || (*data == 'f') || (*data == 's') || (*data == 'c')))
        Error_Notice();
}

/** 
 * @brief - Calculate Factorial of n using Recursion
 * @param n - signed int 32 bit n 
 * @retval - Factorial of n 
 */
uint32_t Factorial(int32_t n)
{
    /* Check if n <0 --> Return 0 --> Error */
    if (n < 0)
        return 0;

    /* Using Recursion to Calculate Factorial */
    if ((n == 1) || (n == 0))
        return 1;
    return n * Factorial(n - 1);
}

/** 
 * @brief - Check n is a prime number
 * @param n - signed int 32bits n
 * @retval - Return true if it's a Prime number, False if it isn't
 */
bool Prime(int32_t n)
{
    int32_t j;
    if (n < 2)
        return false;
    else
    {
        for (j = 2; j <= sqrt(n); j++)
        {
            if ((n % j) == 0)
                return false;
        }
    }
    return true;
}

void Integer_Fac(int32_t n)
{
    int32_t j;
    char num[15];
    if (n < 0)
        strcpy(Result, "Math Error");
    else
    {
        strcpy(Result, "");
        for (j = 2; j <= n; j++)
        {
            while (n % j == 0)
            {
                sprintf(num, "%d ", j);
                strcat(Result, num);
                n /= j;
            }
        }
    }
}


/** 
 * @brief - Calculate 2 integer number is inputted from keyboard
 * @param - None
 * @param Result - The Result of Calculation is save as string type
 * @retval - None
 */
void Serial_Cal(void)
{
    DBG("%s\n", msg1);
    DBG("%s\n", msg2);
    /* Check the Enter button is Pressed */
    while (check_uart != 1)
        ;
    /* Clear check bit */
    check_uart = 0;
    /* Check str is number?? */
    Check_Number(str);
    /* Convert string to int */
    num1 = atoi(str);

    DBG("%s\n", msg4);
    /* Check the Enter button is Pressed */
    while (check_uart != 1)
        ;
    /* Check Operator is correct */
    Check_Oper(str);
    Operation = *str;
    check_uart = 0;
    /* Check Operator must use two number num1 and num2 to calculate */
    if (!((Operation == '!') || (Operation == '?') || (Operation == 'f') || (Operation == 's') || (Operation == 'c') || (Operation == 'r')))
    {
        /* If Operator is +, -, *, /, ^,... */
        /* Input num2 */
        DBG("%s\n", msg3);
        while (check_uart != 1)
            ;
        Check_Number(str);
        check_uart = 0;
        num2 = atoi(str);
        DBG("%s\n", msg5);
        switch (Operation)
        {
        case '+':
            sprintf(Result, "%d", num1 + num2);
            DBG("%s\n", Result);
            break;
        case '-':
            sprintf(Result, "%d", num1 - num2);
            DBG("%s\n", Result);
            break;
        case '*':
            sprintf(Result, "%d", num1 * num2);
            DBG("%s\n", Result);
            break;
        case '/':
            if (num2 == 0)
                Error_Notice();
            sprintf(Result, "%0.4f", (float)num1 / (float)num2);
            DBG("%s\n", Result);
            break;
        case '^':
            sprintf(Result, "%0.1f", pow(num1, num2));
            DBG("%s\n", Result);
        }
    }
    /* If operator using only number 1 */
    /* Operator is f, !, ?, s, c, r */
    else
    {
        DBG("%s\n", msg5);
        switch (Operation)
        {
        case 'f':
            Integer_Fac(num1);
            DBG("%s\n", Result);
            break;
        case '!':
            sprintf(Result, "%d", Factorial(num1));
            DBG("%s\n", Result);
            break;
        case '?':
            if (Prime(num1) == true)
            {
                DBG("This is Prime Number\n");
            }
            else
            {
                DBG("This isn't Prime Number\n");
            }
            break;
        case 's':
            sprintf(Result, "%0.4f", sin(num1 * PI / 180));
            DBG("%s\n", Result);
            break;
        case 'c':
            sprintf(Result, "%0.4f", cos(num1 * PI / 180));
            DBG("%s\n", Result);
            break;
        case 'r':
            sprintf(Result, "%0.4f", sqrt(num1));
            DBG("%s\n", Result);
            break;
        }
    }
}
