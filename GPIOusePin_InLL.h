
#ifndef __GPIOUSEPIN_H
#define __GPIOUSEPIN_H



#include "gpio.h"

static inline char GPIOreadPin(GPIO_TypeDef *GPIOx, uint32_t PinNum)
{
	unsigned long int PortTmp=0;
	PortTmp=LL_GPIO_ReadInputPort(GPIOx);
	return (PortTmp>>PinNum)&0x01;
}

static inline char GPIOreadOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinNum)
{
	unsigned long int PortTmp=0;
	PortTmp=LL_GPIO_ReadOutputPort(GPIOx);
	return (PortTmp>>PinNum)&0x01;
}



static inline void GPIOwritePin(GPIO_TypeDef *GPIOx, uint32_t PinNum,char PinState)
{
	unsigned long int PortTmp=0;
	PortTmp=LL_GPIO_ReadOutputPort(GPIOx);
	if(PinState)//置1
	{
		PortTmp=PortTmp | (0x01<<PinNum);
	}
	else//置0
	{
		PortTmp=PortTmp &~ (0x01<<PinNum);
	}
	LL_GPIO_WriteOutputPort(GPIOx, PortTmp);
}


#endif
