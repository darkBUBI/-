/*
 * hcsr04.h
 *
 *  Created on: Nov 1, 2021
 *      Author: Shinelon
 */

#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_

#define	Trig0	1


#define	Trig0_H		GPIOD->BSRR=1<<Trig0
#define Trig0_L		GPIOD->BSRR=(1<<Trig0)<<16

void Delay_Us(unsigned int time);  //��ʱ����
float Hcsr04GetLength(int num);
#endif /* INC_HCSR04_H_ */
