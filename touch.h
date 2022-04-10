//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F407ZGT6,����ԭ��Explorer STM32F4������,��Ƶ168MHZ������12MHZ
//QDtech-TFTҺ������ for STM32 IOģ��
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/08/09
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
//     LCDģ��                STM32��Ƭ��
//      VCC          ��        DC5V/3.3V      //��Դ
//      GND          ��          GND          //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI����
//     LCDģ��                STM32��Ƭ��    
//    SDI(MOSI)      ��          PB5          //Һ����SPI��������д�ź�
//    SDO(MISO)      ��          PB4          //Һ����SPI�������ݶ��źţ��������Ҫ�������Բ�����
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      STM32��Ƭ�� 
//       LED         ��          PB13         //Һ������������źţ��������Ҫ���ƣ���5V��3.3V
//       SCK         ��          PB3          //Һ����SPI����ʱ���ź�
//      DC/RS        ��          PB14         //Һ��������/��������ź�
//       RST         ��          PB12         //Һ������λ�����ź�
//       CS          ��          PB15         //Һ����Ƭѡ�����ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��                STM32��Ƭ�� 
//      T_IRQ        ��          PB1          //�����������ж��ź�
//      T_DO         ��          PB2          //������SPI���߶��ź�
//      T_DIN        ��          PF11         //������SPI����д�ź�
//      T_CS         ��          PC5          //������Ƭѡ�����ź�
//      T_CLK        ��          PB0          //������SPI����ʱ���ź�
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
#ifndef __TOUCH_H__
#define __TOUCH_H__
//#include "sys.h"

#define TP_PRES_DOWN 0x80  //触屏被按下
#define TP_CATH_PRES 0x40  //�а��������� 	  
										    
//������������
typedef struct
{
	unsigned char (*init)(void);			//��ʼ��������������
	unsigned char (*scan)(unsigned char);				//ɨ�败����.0,��Ļɨ��;1,��������;
	void (*adjust)(void);		//������У׼
	unsigned short int x0;						//ԭʼ����(��һ�ΰ���ʱ������)
	unsigned short int y0;
	unsigned short int x; 						//��ǰ����(�˴�ɨ��ʱ,����������)
	unsigned short int y;
	unsigned char  sta;					//�ʵ�״̬
								//b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������.         			  
////////////////////////������У׼����/////////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//touchtype=0��ʱ��,�ʺ�����ΪX����,����ΪY�����TP.
//touchtype=1��ʱ��,�ʺ�����ΪY����,����ΪX�����TP.
	unsigned char touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��

//�봥����оƬ��������	   
//�봥����оƬ��������

//#define TOUCH_PEN  		0//T_PEN	PCin(0)
//#define TOUCH_DOUT 		1//T_MISO	PCin(1)
#define TOUCH_TDIN 		2	//T_MOSI	PCout(2)
#define TOUCH_TCLK 		3	//T_SCK	PCout(3)
#define TOUCH_TCS  		13	//T_CS	PCout(13)

#define	TDIN_1	GPIOC->BSRR=1<<TOUCH_TDIN
#define	TDIN_0	GPIOC->BSRR=(1<<TOUCH_TDIN)<<16

#define	TCLK_1	GPIOC->BSRR=1<<TOUCH_TCLK
#define	TCLK_0	GPIOC->BSRR=(1<<TOUCH_TCLK)<<16

#define	TCS_1	GPIOC->BSRR=1<<TOUCH_TCS
#define	TCS_0	GPIOC->BSRR=(1<<TOUCH_TCS)<<16

	   
void TP_Write_Byte(unsigned char num);						//�����оƬд��һ������
unsigned short int TP_Read_AD(unsigned char CMD);							//��ȡADת��ֵ
unsigned short int TP_Read_XOY(unsigned char xy);							//���˲��������ȡ(X/Y)
unsigned char TP_Read_XY(unsigned short int *x,unsigned short int *y);					//˫�����ȡ(X+Y)
unsigned char TP_Read_XY2(unsigned short int *x,unsigned short int *y);					//����ǿ�˲���˫���������ȡ
void TP_Drow_Touch_Point(unsigned short int x,unsigned short int y,unsigned short int color);//��һ������У׼��
void TP_Draw_Big_Point(unsigned short int x,unsigned short int y,unsigned short int color);	//��һ�����
unsigned char TP_Scan(unsigned char tp);								//ɨ��
void TP_Save_Adjdata(void);						//����У׼����
unsigned char TP_Get_Adjdata(void);						//��ȡУ׼����
void TP_Adjust(void);							//������У׼
unsigned char TP_Init(void);								//��ʼ��
																 
void TP_Adj_Info_Show(unsigned short int x0,unsigned short int y0,unsigned short int x1,unsigned short int y1,unsigned short int x2,unsigned short int y2,unsigned short int x3,unsigned short int y3,unsigned short int fac);//��ʾУ׼��Ϣ
 		  
#endif

















