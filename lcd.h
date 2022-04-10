//////////////////////////////////////////////////////////////////////////////////	 
//锟斤拷锟斤拷锟斤拷只锟斤拷学习使锟矫ｏ拷未锟斤拷锟斤拷锟斤拷锟斤拷桑锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷魏锟斤拷锟酵�
//锟斤拷锟斤拷硬锟斤拷锟斤拷锟斤拷片锟斤拷STM32F103RCT6,锟斤拷锟斤拷原锟斤拷MiniSTM32锟斤拷锟斤拷锟斤拷,锟斤拷频72MHZ锟斤拷锟斤拷锟斤拷12MHZ
//QDtech-TFT液锟斤拷锟斤拷锟斤拷 for STM32 IO模锟斤拷
//xiao锟斤拷@ShenZhen QDtech co.,LTD
//锟斤拷司锟斤拷站:www.qdtft.com
//锟皆憋拷锟斤拷站锟斤拷http://qdtech.taobao.com
//wiki锟斤拷锟斤拷锟斤拷站锟斤拷http://www.lcdwiki.com
//锟斤拷司锟结供锟斤拷锟斤拷支锟街ｏ拷锟轿何硷拷锟斤拷锟斤拷锟解欢迎锟斤拷时锟斤拷锟斤拷学习
//锟教伙拷(锟斤拷锟斤拷) :+86 0755-23594567
//锟街伙拷:15989313508锟斤拷锟诫工锟斤拷
//锟斤拷锟斤拷:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//锟斤拷锟斤拷支锟斤拷QQ:3002773612  3002778157
//锟斤拷锟斤拷锟斤拷锟斤拷QQ群:324828016
//锟斤拷锟斤拷锟斤拷锟斤拷:2018/08/09
//锟芥本锟斤拷V1.0
//锟斤拷权锟斤拷锟叫ｏ拷锟斤拷锟斤拷鼐锟斤拷锟�
//Copyright(C) 锟斤拷锟斤拷锟斤拷全锟斤拷锟斤拷锟接硷拷锟斤拷锟斤拷锟睫癸拷司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================锟斤拷源锟斤拷锟斤拷================================================//
//     LCD模锟斤拷                STM32锟斤拷片锟斤拷
//      VCC          锟斤拷        DC5V/3.3V      //锟斤拷源
//      GND          锟斤拷          GND          //锟斤拷源锟斤拷
//=======================================液锟斤拷锟斤拷锟斤拷锟斤拷锟竭斤拷锟斤拷==========================================//
//锟斤拷模锟斤拷默锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷为SPI锟斤拷锟斤拷
//     LCD模锟斤拷                STM32锟斤拷片锟斤拷
//    SDI(MOSI)      锟斤拷          PB15         //液锟斤拷锟斤拷SPI锟斤拷锟斤拷锟斤拷锟斤拷写锟脚猴拷
//    SDO(MISO)      锟斤拷          PB14         //液锟斤拷锟斤拷SPI锟斤拷锟斤拷锟斤拷锟捷讹拷锟脚号ｏ拷锟斤拷锟斤拷锟斤拷锟揭拷锟斤拷锟斤拷锟斤拷圆锟斤拷锟斤拷锟�
//=======================================液锟斤拷锟斤拷锟斤拷锟斤拷锟竭斤拷锟斤拷==========================================//
//     LCD模锟斤拷 					      STM32锟斤拷片锟斤拷
//       LED         锟斤拷          PB9          //液锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷藕牛锟斤拷锟斤拷锟斤拷锟斤拷要锟斤拷锟狡ｏ拷锟斤拷5V锟斤拷3.3V
//       SCK         锟斤拷          PB13         //液锟斤拷锟斤拷SPI锟斤拷锟斤拷时锟斤拷锟脚猴拷
//      DC/RS        锟斤拷          PB10         //液锟斤拷锟斤拷锟斤拷锟斤拷/锟斤拷锟斤拷锟斤拷锟斤拷藕锟�
//       RST         锟斤拷          PB12         //液锟斤拷锟斤拷锟斤拷位锟斤拷锟斤拷锟脚猴拷
//       CS          锟斤拷          PB11         //液锟斤拷锟斤拷片选锟斤拷锟斤拷锟脚猴拷
//=========================================锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷=========================================//
//锟斤拷锟侥ｏ拷椴伙拷锟斤拷锟斤拷锟斤拷锟斤拷芑锟斤拷叽锟斤拷写锟斤拷锟斤拷锟斤拷埽锟斤拷锟斤拷遣锟斤拷锟揭拷锟斤拷锟斤拷锟斤拷埽锟斤拷锟斤拷锟揭拷锟斤拷写锟斤拷锟斤拷锟斤拷锟斤拷锟�
//	   LCD模锟斤拷                STM32锟斤拷片锟斤拷
//      T_IRQ        锟斤拷          PC10         //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟叫讹拷锟脚猴拷
//      T_DO         锟斤拷          PC2          //锟斤拷锟斤拷锟斤拷SPI锟斤拷锟竭讹拷锟脚猴拷
//      T_DIN        锟斤拷          PC3          //锟斤拷锟斤拷锟斤拷SPI锟斤拷锟斤拷写锟脚猴拷
//      T_CS         锟斤拷          PC13         //锟斤拷锟斤拷锟斤拷片选锟斤拷锟斤拷锟脚猴拷
//      T_CLK        锟斤拷          PC0          //锟斤拷锟斤拷锟斤拷SPI锟斤拷锟斤拷时锟斤拷锟脚猴拷
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/	
#ifndef __LCD_H
#define __LCD_H		
//#include "sys.h"
#include "stdlib.h"
#include "gpio.h"
//#define unsigned int short unsigned int
//#define unsigned long int unsigned long int
//#define unsigned char	unsigned char
//LCD锟斤拷要锟斤拷锟斤拷锟斤拷
typedef struct  
{										    
	unsigned int width;			//LCD 锟斤拷锟�
	unsigned int height;			//LCD 锟竭讹拷
	unsigned int id;				  //LCD ID
	unsigned char  dir;			  //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟狡ｏ拷0锟斤拷锟斤拷锟斤拷锟斤拷1锟斤拷锟斤拷锟斤拷锟斤拷
	unsigned int	 wramcmd;		//锟斤拷始写gram指锟斤拷
	unsigned int  setxcmd;		//锟斤拷锟斤拷x锟斤拷锟斤拷指锟斤拷
	unsigned int  setycmd;		//锟斤拷锟斤拷y锟斤拷锟斤拷指锟斤拷
}_lcd_dev; 	

//LCD锟斤拷锟斤拷
extern _lcd_dev lcddev;	//锟斤拷锟斤拷LCD锟斤拷要锟斤拷锟斤拷
/////////////////////////////////////锟矫伙拷锟斤拷锟斤拷锟斤拷///////////////////////////////////
#define USE_HORIZONTAL  	 0//锟斤拷锟斤拷液锟斤拷锟斤拷顺时锟斤拷锟斤拷转锟斤拷锟斤拷 	0-0锟斤拷锟斤拷转锟斤拷1-90锟斤拷锟斤拷转锟斤拷2-180锟斤拷锟斤拷转锟斤拷3-270锟斤拷锟斤拷转

//////////////////////////////////////////////////////////////////////////////////	  
//锟斤拷锟斤拷LCD锟侥尺达拷
#define LCD_W 240
#define LCD_H 320

//TFTLCD锟斤拷锟斤拷锟斤拷要锟斤拷锟矫的猴拷锟斤拷
extern unsigned int  POINT_COLOR;//默锟较猴拷色
extern unsigned int  BACK_COLOR; //锟斤拷锟斤拷锟斤拷色.默锟斤拷为锟斤拷色

////////////////////////////////////////////////////////////////////
//-----------------LCD锟剿口讹拷锟斤拷----------------
#define GPIO_TYPE  GPIOA  //GPIO锟斤拷锟斤拷锟斤拷
#define LED      9        //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�        PB9
#define LCD_CS   2       //片选锟斤拷锟斤拷            PB11
#define LCD_RS   0     //锟侥达拷锟斤拷/锟斤拷锟斤拷选锟斤拷锟斤拷锟斤拷 PB10
#define LCD_RST  1      //锟斤拷位锟斤拷锟斤拷            PB12
#define SPI_MOSI   7     //锟侥达拷锟斤拷/锟斤拷锟斤拷选锟斤拷锟斤拷锟斤拷 PB10
#define SPI_SCLK  5      //锟斤拷位锟斤拷锟斤拷            PB12

//QDtech全系锟斤拷模锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷芸锟斤拷票锟斤拷锟斤拷锟斤拷锟斤拷没锟揭诧拷锟斤拷越锟絇WM锟斤拷锟节憋拷锟斤拷锟斤拷锟斤拷
#define	LCD_LED PBout(LED) //LCD锟斤拷锟斤拷    		 PB9
//锟斤拷锟绞癸拷霉俜锟斤拷夂拷锟斤拷锟斤拷锟斤拷锟斤拷械撞悖拷俣冉锟斤拷锟斤拷陆锟斤拷锟�14帧每锟诫，锟斤拷锟斤拷锟斤拷锟斤拷锟剿撅拷萍锟斤拷锟斤拷锟�
//锟斤拷锟斤拷IO锟斤拷锟斤拷直锟接诧拷锟斤拷锟侥达拷锟斤拷锟斤拷锟斤拷锟斤拷IO锟斤拷锟斤拷锟斤拷刷锟斤拷锟斤拷锟绞匡拷锟皆达到28帧每锟诫！

//GPIO锟斤拷位锟斤拷锟斤拷锟竭ｏ拷
#define	LCD_CS_SET  	GPIO_TYPE->BSRR=1<<LCD_CS//GPIOwritePin(GPIOA,2,1) //   //片选锟剿匡拷  	PB11	pc2
#define	LCD_RS_SET		GPIO_TYPE->BSRR=1<<LCD_RS //GPIOwritePin(GPIOA,0,1)//   //锟斤拷锟斤拷/锟斤拷锟斤拷  PB10		pc0
#define	LCD_RST_SET		GPIO_TYPE->BSRR=1<<LCD_RST//GPIOwritePin(GPIOA,1,1)///   //锟斤拷位			  PB12		pc1

//GPIO锟斤拷位锟斤拷锟斤拷锟酵ｏ拷
#define	LCD_CS_CLR  	GPIO_TYPE->BSRR=(1<<LCD_CS)<<16// GPIOwritePin(GPIOA,2,0)//    //片选锟剿匡拷  	PB11
#define	LCD_RS_CLR		GPIO_TYPE->BSRR=(1<<LCD_RS)<<16 //GPIOwritePin(GPIOA,0,0)//	    //锟斤拷锟斤拷/锟斤拷锟斤拷  PB10
#define	LCD_RST_CLR		GPIO_TYPE->BSRR=(1<<LCD_RST)<<16//GPIOwritePin(GPIOA,1,0)//    //锟斤拷位			  PB12




//#define GPIO_TYPE  GPIOA  //GPIO锟斤拷锟斤拷锟斤拷




///*test*/
#define	SPI_MOSI_SET  	GPIOwritePin(GPIOA,7,1)//GPIO_TYPE->BSRR=1<<SPI_MOSI//////
#define	SPI_SCLK_SET  	GPIOwritePin(GPIOA,5,1)//GPIO_TYPE->BSRR=1<<SPI_SCLK//////


//娑叉櫠鎺у埗鍙ｇ疆0鎿嶄綔璇彞瀹忓畾涔�

#define	SPI_MOSI_CLR  	GPIOwritePin(GPIOA,7,0)//GPIO_TYPE->BSRR=(1<<SPI_MOSI)<<16//////
#define	SPI_SCLK_CLR  	GPIOwritePin(GPIOA,5,0)//GPIO_TYPE->BSRR=(1<<SPI_SCLK)<<16//////







//锟斤拷锟斤拷锟斤拷色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //锟斤拷色
#define BRRED 			0XFC07 //锟截猴拷色
#define GRAY  			0X8430 //锟斤拷色
//GUI锟斤拷色

#define DARKBLUE      	 0X01CF	//锟斤拷锟斤拷色
#define LIGHTBLUE      	 0X7D7C	//浅锟斤拷色
#define GRAYBLUE       	 0X5458 //锟斤拷锟斤拷色
//锟斤拷锟斤拷锟斤拷色为PANEL锟斤拷锟斤拷色
 
#define LIGHTGREEN     	0X841F //浅锟斤拷色
#define LIGHTGRAY     0XEF5B //浅锟斤拷色(PANNEL)
#define LGRAY 			 		0XC618 //浅锟斤拷色(PANNEL),锟斤拷锟藉背锟斤拷色

#define LGRAYBLUE      	0XA651 //浅锟斤拷锟斤拷色(锟叫硷拷锟斤拷锟缴�)
#define LBBLUE          0X2B12 //浅锟斤拷锟斤拷色(选锟斤拷锟斤拷目锟侥凤拷色)







void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);

void LCD_Clear(unsigned int Color);
void LCD_SetCursor(unsigned int Xpos, unsigned int Ypos);
void LCD_DrawPoint(unsigned int x,unsigned int y);//锟斤拷锟斤拷
unsigned int  LCD_ReadPoint(unsigned int x,unsigned int y); //锟斤拷锟斤拷
void LCD_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_DrawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_SetWindows(unsigned int xStar, unsigned int yStar,unsigned int xEnd,unsigned int yEnd);

unsigned int LCD_RD_DATA(void);//锟斤拷取LCD锟斤拷锟斤拷
void LCD_WriteReg(unsigned char LCD_Reg, unsigned int LCD_RegValue);
void LCD_WR_DATA(unsigned char data);
unsigned int LCD_ReadReg(unsigned char LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(unsigned int RGB_Code);
unsigned int LCD_ReadRAM(void);
unsigned int LCD_BGR2RGB(unsigned int c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(unsigned int Data);
void LCD_direction(unsigned char direction );
void LCD_WriteData_Color(unsigned int color);

void Lcd_WriteData_16Bit_OV(unsigned int data);
//锟斤拷锟斤拷锟饺伙拷锟斤拷锟斤拷俣炔锟斤拷锟斤拷欤拷锟斤拷锟绞癸拷锟斤拷锟斤拷锟侥宏定锟斤拷,锟斤拷锟斤拷俣锟�.
//注锟斤拷要去锟斤拷lcd.c锟斤拷void LCD_WR_DATA(unsigned int data)锟斤拷锟斤拷锟斤拷锟斤拷哦
/*
#if LCD_USE8BIT_MODEL==1//使锟斤拷8位锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷模式
	#define LCD_WR_DATA(data){\
	LCD_RS_SET;\
	LCD_CS_CLR;\
	DATAOUT(data);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	DATAOUT(data<<8);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	LCD_CS_SET;\
	}
	#else//使锟斤拷16位锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷模式
	#define LCD_WR_DATA(data){\
	LCD_RS_SET;\
	LCD_CS_CLR;\
	DATAOUT(data);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	LCD_CS_SET;\
	} 	
#endif
*/
				  		 
#endif  
	 
	 



