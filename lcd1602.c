#include "lcd1602.h"
/**/
GPIO_TypeDef * LCD_8bit_GPIOport=GPIOB;//8λ���ж˿�
uint16_t LCD_8bit_GPIOlsb=8;//8λ�������λ
uint16_t LCD_8bit_GPIOmusk= 0xFF <<8;
//LCD_8bit_GPIOmusk= 0xFF <<LCD_8bit_GPIOlsb //�����﷨

GPIO_TypeDef * LCD_RS_GPIOport=GPIOB;//RS�Ķ˿�
uint16_t LCD_RS_PinMusk=0x01<<6;//RS������

GPIO_TypeDef * LCD_RW_GPIOport=GPIOB;//RW�Ķ˿�
uint16_t LCD_RW_PinMusk=0x01<<5;//RW������

GPIO_TypeDef * LCD_EN_GPIOport=GPIOB;//EN�Ķ˿�
uint16_t LCD_EN_PinMusk=0x01<<7;//EN������

void lcd_send_cmd (unsigned int cmd)
{
	unsigned int temp;//�����洢��gpiox��ȡ����16λ��
//	LL_melay(1);
	temp=LL_GPIO_ReadOutputPort(LCD_RS_GPIOport);
	LL_GPIO_WriteOutputPort(LCD_RS_GPIOport, temp &~ LCD_RS_PinMusk);//RS=0
	LL_mDelay(1);

  	temp=LL_GPIO_ReadOutputPort(LCD_8bit_GPIOport);//Ӧ��ReadOutputPort�Ŷԡ�
  	temp=temp &~ LCD_8bit_GPIOmusk;
  	cmd=cmd<<LCD_8bit_GPIOlsb;
  	temp=temp | cmd;
  	LL_GPIO_WriteOutputPort(LCD_8bit_GPIOport, temp);//

//  	LL_melay(1);
  	temp=LL_GPIO_ReadOutputPort(LCD_EN_GPIOport);
  	LL_GPIO_WriteOutputPort(LCD_EN_GPIOport, temp | LCD_EN_PinMusk);//EN=1
  	LL_mDelay(1);
  	temp=LL_GPIO_ReadOutputPort(LCD_EN_GPIOport);
  	LL_GPIO_WriteOutputPort(LCD_EN_GPIOport, temp &~ LCD_EN_PinMusk);//en=0

}

void lcd_send_data (unsigned int data)
{
	unsigned int a;

	a=LL_GPIO_ReadOutputPort(LCD_RS_GPIOport);
    LL_GPIO_WriteOutputPort(LCD_RS_GPIOport, a | LCD_RS_PinMusk);//RS=1

    LL_mDelay(1);

    a=LL_GPIO_ReadOutputPort(LCD_8bit_GPIOport);
    a=a &~ LCD_8bit_GPIOmusk;
    data=data<<LCD_8bit_GPIOlsb;
    a=a | data;
    LL_GPIO_WriteOutputPort(LCD_8bit_GPIOport, a);//cmd | 0x80

//    LL_melay(1);
    a=LL_GPIO_ReadOutputPort(LCD_EN_GPIOport);
    LL_GPIO_WriteOutputPort(LCD_EN_GPIOport, a | LCD_EN_PinMusk);//EN=1
    LL_mDelay(1);
    a=LL_GPIO_ReadOutputPort(LCD_EN_GPIOport);
    LL_GPIO_WriteOutputPort(LCD_EN_GPIOport, a &~ LCD_EN_PinMusk);//en=0


}

void lcd_init (void)
{
	unsigned int a;
	a=LL_GPIO_ReadOutputPort(LCD_RW_GPIOport);
    LL_GPIO_WriteOutputPort(LCD_RW_GPIOport, a &~ LCD_RW_PinMusk);//RW=0


    lcd_send_cmd (0x38); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
    //LL_melay(1);
    //lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
    //LL_melay(1);
    lcd_send_cmd (0x01);  // clear display
   // LL_melay(1);
   // LL_melay(1);
    lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
   // LL_melay(1);
    lcd_send_cmd (0x0F); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)


}

void lcd_send_string(char *str){
//  lcd_send_cmd(a | 0x80);
	while(*str != '\0')
	{
		lcd_send_data(*str++);
	}
	*str = 0;
}

