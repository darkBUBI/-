/*
 * hcsr04.c
 *
 *  Created on: Nov 1, 2021
 *      Author: Shinelon
 */
#include "GPIOusePin_InLL.h"
//#include "usart.h"
#include "hcsr04.h"
extern int flag;
extern float	Acoustic_velocity;
void Delay_Us(unsigned int time)  //��ʱ����
{
	unsigned int i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<9;j++);
}

float Hcsr04GetLength(int num)
{
	float length=0;
	unsigned long int time=0;

	GPIOwritePin(GPIOD, num*2+1, 1);//Trig0_H;////����һ������10us�ķ���		Trig_Pin
	Delay_Us(15);
	GPIOwritePin(GPIOD, num*2+1, 0);//Trig0_L;//

	LL_TIM_SetCounter(TIM1, 0);
	while((GPIOreadPin(GPIOD, num*2) == 0));			//Echo_Pin
	LL_TIM_EnableCounter(TIM1);
	while((GPIOreadPin(GPIOD, num*2)) == 1 );
	LL_TIM_DisableCounter(TIM1);
	time=LL_TIM_GetCounter(TIM1);
	LL_TIM_SetCounter(TIM1, 0);
//	if(flag==1)
//	{
//		flag=0;
//		return 500;
//	}

//	length=(float)time/58.0;//
	length=(float)time*0.00005*Acoustic_velocity;
	return length;
}
