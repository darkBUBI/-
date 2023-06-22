/*
 * checkbusy.c
 *
 *  Created on: Oct 25, 2021
 *      Author: Shinelon
 */
#include "usart.h"
void check()
{
	unsigned char rebuff[10]={"0"};
	HAL_UART_Receive(&huart1, rebuff, 4, 70);

}
