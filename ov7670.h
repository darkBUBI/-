#ifndef _OV7670_H
#define _OV7670_H
//#include "system.h"
#include "sccb.h"
#include "GPIOusePin_InLL.h"
//#include "gpio.h"
//#include "main.h"
 //gpioc
#define WRST	9
#define	WREN	8
#define	RCK		7
#define	RRST	6
//#define OV7670_VSYNC  	PAin(8)			//ͬ���źż��IO
//#define OV7670_WRST		PCout(9)		//дָ�븴λ
//#define OV7670_WREN		PCout(8)		//д��FIFOʹ��
#define OV7670_RCK_H	GPIOC->BSRR=1<<RCK			//GPIOwritePin(GPIOA,13,1)//���ö�����ʱ�Ӹߵ�ƽ   PC 7 1
#define OV7670_RCK_L	GPIOC->BSRR=(1<<RCK)<<16	//GPIOwritePin(GPIOA,13,0)//���ö�����ʱ�ӵ͵�ƽ 	 0
//#define OV7670_RRST		PCout(6)  		//��ָ�븴λ
//#define OV7670_CS		PAout(15)  		//Ƭѡ�ź�(OE)

#define OV7670_DATA   GPIOD->IDR&0xFF00//GPIOB->IDR&0xFF00  //��������˿�	D8-D15
/////////////////////////////////////////									



#define OV7670_WRST_1   GPIOC->BSRR=1<<WRST			//GPIOwritePin(GPIOA,11,1)
#define OV7670_WRST_0   GPIOC->BSRR=(1<<WRST)<<16  	//GPIOwritePin(GPIOA,11,0)

#define OV7670_WREN_1	GPIOC->BSRR=1<<WREN			//GPIOwritePin(GPIOA,12,1)
#define OV7670_WREN_0	GPIOC->BSRR=(1<<WREN)<<16	//GPIOwritePin(GPIOA,12,0)

#define OV7670_RRST_1   GPIOC->BSRR=1<<RRST			//GPIOwritePin(GPIOA,14,1)
#define OV7670_RRST_0   GPIOC->BSRR=(1<<RRST)<<16	//GPIOwritePin(GPIOA,14,0)

unsigned char   OV7670_Init(void);
void OV7670_Light_Mode(unsigned char mode);
void OV7670_Color_Saturation(unsigned char sat);
void OV7670_Brightness(unsigned char bright);
void OV7670_Contrast(unsigned char contrast);
void OV7670_Special_Effects(unsigned char eft);
void OV7670_Window_Set(unsigned int sx,unsigned int sy,unsigned int width,unsigned int height);
void EXTI8_Init(void);




#endif
