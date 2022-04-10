#ifndef __SCCB_H
#define __SCCB_H
//#include "system.h"
#include "GPIOusePin_InLL.h"
//#include "gpio.h"
//#include "main.h"
  
//#define SCCB_SDA_IN()  {GPIOG->CRH&=0XFF0FFFFF;GPIOG->CRH|=0X00800000;}//PG13
//#define SCCB_SDA_OUT() {GPIOG->CRH&=0XFF0FFFFF;GPIOG->CRH|=0X00300000;}

//输出模式（50Mhz）通用推挽输出模式
//#define SCCB_SDA_OUT() 	{GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=3<<16;}//{GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=3<<28;}//2*14=28
//输入模式上拉/下拉输入模式
//#define SCCB_SDA_IN()	{GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=8<<16;}//{GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=8<<28;}


#define SCCB_SDA_OUT()	{GPIOB->MODER &= ~(3<<(7*2));GPIOB->MODER |= 1<<7*2;GPIOB->OSPEEDR &= ~(3<<(7*2));GPIOB->OSPEEDR |= 2<<7*2;GPIOB->OTYPER &= ~(0<<7);} //PB7输出模式50MHZ 通用推挽输出模式
						//清空位置					写0X01输出				清空		0X11<<14			写0X10，50MHZ				清空，写0推挽输出
#define SCCB_SDA_IN()	{GPIOB->MODER &= ~(3<<(7*2));GPIOB->MODER |= 0<<7*2;GPIOB->PUPDR &= ~(3<<(7*2));GPIOB->PUPDR |=1<<2*7;}	//PB7输入模式上拉

//IO��������

#define	SCL		6
#define	SDA 	7

#define SCCB_SCL_1    		GPIOB->BSRR=1<<SCL//GPIOwritePin(GPIOB,6,1)//PAout(11)	 	//SCL
#define SCCB_SCL_0    		GPIOB->BSRR=(1<<SCL)<<16//GPIOwritePin(GPIOB,6,0)
#define SCCB_SDA_1    		GPIOB->BSRR=1<<SDA//GPIOwritePin(GPIOB,7,1)//PAout(12) 		//SDA
#define SCCB_SDA_0  		GPIOB->BSRR=(1<<SDA)<<16//GPIOwritePin(GPIOB,7,0)

//#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
//#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
//
//#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))
//#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010808
//#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入

//#define SCCB_READ_SDA    	PBin(7) // 		//����SDA
#define SCCB_READ_SDA  		GPIOreadPin(GPIOB,7)//GPIOreadPin(GPIOA,12)//

#define SCCB_ID   			0X42  			//OV7670��ID

///////////////////////////////////////////
void delay_us(unsigned int t);
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
unsigned char SCCB_WR_Byte(unsigned char dat);
unsigned char SCCB_RD_Byte(void);
unsigned char SCCB_WR_Reg(unsigned char reg,unsigned char data);
unsigned char SCCB_RD_Reg(unsigned char reg);
//void SCCB_SDA_IN(void);
//void SCCB_SDA_OUT(void);
#endif













