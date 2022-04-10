//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RCT6,����ԭ��MiniSTM32������,��Ƶ72MHZ������12MHZ
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
//    SDI(MOSI)      ��          PB15         //Һ����SPI��������д�ź�
//    SDO(MISO)      ��          PB14         //Һ����SPI�������ݶ��źţ��������Ҫ�������Բ�����
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      STM32��Ƭ��
//       LED         ��          PB9          //Һ������������źţ��������Ҫ���ƣ���5V��3.3V
//       SCK         ��          PB13         //Һ����SPI����ʱ���ź�
//      DC/RS        ��          PB10         //Һ��������/��������ź�
//       RST         ��          PB12         //Һ������λ�����ź�
//       CS          ��          PB11         //Һ����Ƭѡ�����ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��                STM32��Ƭ��
//      T_IRQ        ��          PC10         //�����������ж��ź�
//      T_DO         ��          PC2          //������SPI���߶��ź�
//      T_DIN        ��          PC3          //������SPI����д�ź�
//      T_CS         ��          PC13         //������Ƭѡ�����ź�
//      T_CLK        ��          PC0          //������SPI����ʱ���ź�
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
#ifndef __GUI_H__
#define __GUI_H__
//#define unsigned int 	unsigned int
//#define unsigned long int  	unsigned long int
//#define unsigned char		unsigned char

void GUI_DrawPoint(unsigned int x,unsigned int y,unsigned int color);
void LCD_Fill(unsigned int sx,unsigned int sy,unsigned int ex,unsigned int ey,unsigned int color);
void LCD_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_DrawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void Draw_Circle(unsigned int x0,unsigned int y0,unsigned int fc,unsigned char r);
void Draw_Triangel(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void Fill_Triangel(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_ShowChar(unsigned int x,unsigned int y,unsigned int fc, unsigned int bc, unsigned char num,unsigned char size,unsigned char mode);
void LCD_ShowNum(unsigned int x,unsigned int y,unsigned long int num,unsigned char len,unsigned char size);
void LCD_Show2Num(unsigned int x,unsigned int y,unsigned int num,unsigned char len,unsigned char size,unsigned char mode);
void LCD_ShowString(unsigned int x,unsigned int y,unsigned char size,unsigned char *p,unsigned char mode);
void GUI_DrawFont16(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc, unsigned char *s,unsigned char mode);
void GUI_DrawFont24(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc, unsigned char *s,unsigned char mode);
void GUI_DrawFont32(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc, unsigned char *s,unsigned char mode);
void Show_Str(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc, unsigned char *str,unsigned char size,unsigned char mode);
void Gui_Drawbmp16(unsigned int x,unsigned int y,const unsigned char *p); //��ʾ40*40 QQͼƬ
void gui_circle(int xc, int yc,unsigned int c,int r, int fill);
void Gui_StrCenter(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc, unsigned char *str,unsigned char size,unsigned char mode);
void LCD_DrawFillRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void Show_Online(uint8_t num);
void Show_Offline(uint8_t num);
#endif

