/*
 * ds18b20.h
 *
 *  Created on: 2022年1月27日
 *      Author: Shinelon
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#include "GPIOusePin_InLL.h"

//IO方向设置
//#define DS18B20_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
//#define DS18B20_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}



//IO操作函数
//#define	DS18B20_DQ_OUT PGout(11) //数据端口	PA0
//#define	DS18B20_DQ_IN  PGin(11)  //数据端口	PA0
#define	DS18B20_OUT		2


#define DS18B20_IO_OUT() 					{GPIOE->MODER &= ~(3<<(DS18B20_OUT*2));GPIOE->MODER |= 1<<DS18B20_OUT*2;GPIOE->OSPEEDR &= ~(3<<(DS18B20_OUT*2));GPIOE->OSPEEDR |= 2<<DS18B20_OUT*2;GPIOE->OTYPER &= ~(0<<DS18B20_OUT);}
//PE2输出模式50MHZ 通用推挽输出模式			//清零								写0X01,通用输出					清零										写0X10 50MHZ						清零,写0X00,pushpull
#define DS18B20_IO_IN()  					{GPIOE->MODER &= ~(3<<(DS18B20_OUT*2));GPIOE->MODER |= 0<<DS18B20_OUT*2;GPIOE->PUPDR &= ~(3<<(DS18B20_OUT*2));GPIOE->PUPDR |=1<<2*DS18B20_OUT;}
//PE2输入模式上拉							//清0									写0X00 输入						清0										写0x01上拉

#define	DS18B20_DQ_OUT_1	GPIOE->BSRR=1<<DS18B20_OUT
#define	DS18B20_DQ_OUT_0	GPIOE->BSRR=(1<<DS18B20_OUT)<<16

#define DS18B20_DQ_IN		GPIOreadPin(GPIOE,2)

unsigned char DS18B20_Init(void);//初始化DS18B20
short DS18B20_Get_Temp(void);//获取温度
void DS18B20_Start(void);//开始温度转换
void DS18B20_Write_Byte(unsigned char dat);//写入一个字节
unsigned char DS18B20_Read_Byte(void);//读出一个字节
unsigned char DS18B20_Read_Bit(void);//读出一个位
unsigned char DS18B20_Check(void);//检测是否存在DS18B20
void DS18B20_Rst(void);//复位DS18B20


#endif /* INC_DS18B20_H_ */
