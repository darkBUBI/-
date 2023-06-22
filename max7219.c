/*
 * max7219.c
 *
 *  Created on: Aug 2, 2021
 *      Author: Shinelon
 */

#include <max7219.h>
#include "GPIOusePin_InLL.h"
#include "delayClockCycles.h"

#define	CS_1()	GPIOwritePin(GPIOA,7,1)
#define	CS_0()	GPIOwritePin(GPIOA,7,0)

#define	CLK_1()	GPIOwritePin(GPIOA,5,1)
#define	CLK_0()	GPIOwritePin(GPIOA,5,0)

#define	DIN_1()	GPIOwritePin(GPIOA,6,1)
#define	DIN_0()	GPIOwritePin(GPIOA,6,0)
//--------------------------------------------
//功能：向MAX7219(U3)写入字节
//入口参数：DATA
//出口参数：无
//说明：
void Write_Max7219_byte(uchar DATA)
{
    	uchar i;
    	CS_1();		//Max7219_pinCS=0;
	    for(i=8;i>=1;i--)
          {
	    	CLK_0();		//            Max7219_pinCLK=0;
	    	GPIOwritePin(GPIOA, 6, DATA&0x80);//            Max7219_pinDIN=DATA&0x80;
            DATA=DATA<<1;
            CLK_1();		//Max7219_pinCLK=1;
           }
}
//-------------------------------------------
//功能：向MAX7219写入数据
//入口参数：address、dat
//出口参数：无
//说明：
void Write_Max7219(uchar address,uchar dat)
{
     CS_0();//Max7219_pinCS=0;
	 Write_Max7219_byte(address);           //写入地址，即数码管编号
     Write_Max7219_byte(dat);               //写入数据，即数码管显示数字
	 CS_1();//Max7219_pinCS=1;
}

void Init_MAX7219(void)
{
 Write_Max7219(0x09, 0xff);       //译码方式：BCD码
 Write_Max7219(0x0a, 0x03);       //亮度
 Write_Max7219(0x0b, 0x07);       //扫描界限；4个数码管显示
 Write_Max7219(0x0c, 0x01);       //掉电模式：0，普通模式：1
 Write_Max7219(0x0f, 0x01);       //显示测试：1；测试结束，正常显示：0
}
