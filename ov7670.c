//#include "system.h"
#include "ov7670.h"
#include "ov7670cfg.h"
#include "time.h"	  
//#include "SysTick.h"
#include "usart.h"			 
#include "sccb.h"	
//#include "stm32f1xx_it.h"
#include "stm32f4xx_it.h"
unsigned char showbuff1[30]={"\0"};

//�ⲿ�ж�8��ʼ��
void EXTI8_Init(void)
{												  
//	LL_EXTI_Init();//EXTI_InitTypeDef EXTI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);//PA8���ж���8
//
//	EXTI_InitStructure.EXTI_Line=EXTI_LINE_8;
//	EXTI_InitStructure.EXTI_Mode = EXTI_MODE_INTERRUPT;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_TRIGGER_RISING;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}


 	    
//��ʼ��OV7670
//����0:�ɹ�
//��������ֵ:�������
unsigned char  OV7670_Init(void)
{
	unsigned char temp=0;
	unsigned int i=0;
	//����IO
//	LL_GPIO_InitTypeDef  GPIO_InitStructure;
// 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO, ENABLE);	 //ʹ����ض˿�ʱ��
// 	  /* GPIO Ports Clock Enable */
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
//	GPIO_InitStructure.Pin  = GPIO_PIN_8; 	//PA8 ���� ����
//	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
//	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA,GPIO_PIN_8);
//
// 	GPIO_InitStructure.Pin = GPIO_PIN_3|GPIO_PIN_4;				 // �˿�����
// 	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 		 //�������
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
// 	GPIO_SetBits(GPIOB,GPIO_PIN_3|GPIO_PIN_4);
//
//	GPIO_InitStructure.Pin  = 0xff00; //PB8~15 ���� ����
//	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
// 	LL_GPIO_Init(GPIOB, &GPIO_InitStructure);//(GPIOB, &GPIO_InitStructure);
//
//	GPIO_InitStructure.Pin  = GPIO_PIN_6;
//	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_Init(GPIOD, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOD,GPIO_PIN_6);
//
//	GPIO_InitStructure.Pin  = GPIO_PIN_14|GPIO_PIN_15;
//	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA,GPIO_PIN_14|GPIO_PIN_15);
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	//SWD
	
 	SCCB_Init();        		//��ʼ��SCCB ��IO��
 	if(SCCB_WR_Reg(0x12,0x80))return 1;	//��λSCCB

 	LL_mDelay(50);//	delay_ms(50);
	//��ȡ��Ʒ�ͺ�
 	temp=SCCB_RD_Reg(0x0b);   
// 	  sprintf(showbuff1,"read ban ben id: %u\n",temp);
// 	  HAL_UART_Transmit(&huart1, showbuff1, 30, 200);
// 	  LL_mDelay(100);
	if(temp!=0x73)return 2;  
 	temp=SCCB_RD_Reg(0x0a);   
	if(temp!=0x76)return 2;
	//��ʼ������
	for(i=0;i<sizeof(ov7670_init_reg_tbl)/sizeof(ov7670_init_reg_tbl[0]);i++)
	{
	   	SCCB_WR_Reg(ov7670_init_reg_tbl[i][0],ov7670_init_reg_tbl[i][1]);
  	}
   	return 0x00; 	//ok
} 
////////////////////////////////////////////////////////////////////////////
//OV7670��������
//��ƽ������
//0:�Զ�
//1:̫��sunny
//2,����cloudy
//3,�칫��office
//4,����home
void OV7670_Light_Mode(unsigned char mode)
{
	unsigned char reg13val=0XE7;//Ĭ�Ͼ�������Ϊ�Զ���ƽ��
	unsigned char reg01val=0;
	unsigned char reg02val=0;
	switch(mode)
	{
		case 1://sunny
			reg13val=0XE5;
			reg01val=0X5A;
			reg02val=0X5C;
			break;	
		case 2://cloudy
			reg13val=0XE5;
			reg01val=0X58;
			reg02val=0X60;
			break;	
		case 3://office
			reg13val=0XE5;
			reg01val=0X84;
			reg02val=0X4c;
			break;	
		case 4://home
			reg13val=0XE5;
			reg01val=0X96;
			reg02val=0X40;
			break;	
	}
	SCCB_WR_Reg(0X13,reg13val);//COM8����
	SCCB_WR_Reg(0X01,reg01val);//AWB��ɫͨ������
	SCCB_WR_Reg(0X02,reg02val);//AWB��ɫͨ������
}				  
//ɫ������
//0:-2
//1:-1
//2,0
//3,1
//4,2
void OV7670_Color_Saturation(unsigned char sat)
{
	unsigned char reg4f5054val=0X80;//Ĭ�Ͼ���sat=2,��������ɫ�ȵ�����
 	unsigned char reg52val=0X22;
	unsigned char reg53val=0X5E;
 	switch(sat)
	{
		case 0://-2
			reg4f5054val=0X40;  	 
			reg52val=0X11;
			reg53val=0X2F;	 	 
			break;	
		case 1://-1
			reg4f5054val=0X66;	    
			reg52val=0X1B;
			reg53val=0X4B;	  
			break;	
		case 3://1
			reg4f5054val=0X99;	   
			reg52val=0X28;
			reg53val=0X71;	   
			break;	
		case 4://2
			reg4f5054val=0XC0;	   
			reg52val=0X33;
			reg53val=0X8D;	   
			break;	
	}
	SCCB_WR_Reg(0X4F,reg4f5054val);	//ɫ�ʾ���ϵ��1
	SCCB_WR_Reg(0X50,reg4f5054val);	//ɫ�ʾ���ϵ��2
	SCCB_WR_Reg(0X51,0X00);			//ɫ�ʾ���ϵ��3
	SCCB_WR_Reg(0X52,reg52val);		//ɫ�ʾ���ϵ��4
	SCCB_WR_Reg(0X53,reg53val);		//ɫ�ʾ���ϵ��5
	SCCB_WR_Reg(0X54,reg4f5054val);	//ɫ�ʾ���ϵ��6
	SCCB_WR_Reg(0X58,0X9E);			//MTXS 
}
//��������
//0:-2
//1:-1
//2,0
//3,1
//4,2
void OV7670_Brightness(unsigned char bright)
{
	unsigned char reg55val=0X00;//Ĭ�Ͼ���bright=2
  	switch(bright)
	{
		case 0://-2
			reg55val=0XB0;	 	 
			break;	
		case 1://-1
			reg55val=0X98;	 	 
			break;	
		case 3://1
			reg55val=0X18;	 	 
			break;	
		case 4://2
			reg55val=0X30;	 	 
			break;	
	}
	SCCB_WR_Reg(0X55,reg55val);	//���ȵ���
}
//�Աȶ�����
//0:-2
//1:-1
//2,0
//3,1
//4,2
void OV7670_Contrast(unsigned char contrast)
{
	unsigned char reg56val=0X40;//Ĭ�Ͼ���contrast=2
  	switch(contrast)
	{
		case 0://-2
			reg56val=0X30;	 	 
			break;	
		case 1://-1
			reg56val=0X38;	 	 
			break;	
		case 3://1
			reg56val=0X50;	 	 
			break;	
		case 4://2
			reg56val=0X60;	 	 
			break;	
	}
	SCCB_WR_Reg(0X56,reg56val);	//�Աȶȵ���
}
//��Ч����
//0:��ͨģʽ
//1,��Ƭ
//2,�ڰ�
//3,ƫ��ɫ
//4,ƫ��ɫ
//5,ƫ��ɫ
//6,����
void OV7670_Special_Effects(unsigned char eft)
{
	unsigned char reg3aval=0X04;//Ĭ��Ϊ��ͨģʽ
	unsigned char reg67val=0XC0;
	unsigned char reg68val=0X80;
	switch(eft)
	{
		case 1://��Ƭ
			reg3aval=0X24;
			reg67val=0X80;
			reg68val=0X80;
			break;	
		case 2://�ڰ�
			reg3aval=0X14;
			reg67val=0X80;
			reg68val=0X80;
			break;	
		case 3://ƫ��ɫ
			reg3aval=0X14;
			reg67val=0Xc0;
			reg68val=0X80;
			break;	
		case 4://ƫ��ɫ
			reg3aval=0X14;
			reg67val=0X40;
			reg68val=0X40;
			break;	
		case 5://ƫ��ɫ
			reg3aval=0X14;
			reg67val=0X80;
			reg68val=0XC0;
			break;	
		case 6://����
			reg3aval=0X14;
			reg67val=0XA0;
			reg68val=0X40;
			break;	 
	}
	SCCB_WR_Reg(0X3A,reg3aval);//TSLB����
	SCCB_WR_Reg(0X68,reg67val);//MANU,�ֶ�Uֵ
	SCCB_WR_Reg(0X67,reg68val);//MANV,�ֶ�Vֵ
}	
//����ͼ���������
//��QVGA���á�
void OV7670_Window_Set(unsigned int sx,unsigned int sy,unsigned int width,unsigned int height)
{
	unsigned int endx;
	unsigned int endy;
	unsigned char temp;
	endx=sx+width*2;	//V*2
 	endy=sy+height*2;
	if(endy>784)endy-=784;
	temp=SCCB_RD_Reg(0X03);				//��ȡVref֮ǰ��ֵ
	temp&=0XF0;
	temp|=((endx&0X03)<<2)|(sx&0X03);
	SCCB_WR_Reg(0X03,temp);				//����Vref��start��end�����2λ
	SCCB_WR_Reg(0X19,sx>>2);			//����Vref��start��8λ
	SCCB_WR_Reg(0X1A,endx>>2);			//����Vref��end�ĸ�8λ

	temp=SCCB_RD_Reg(0X32);				//��ȡHref֮ǰ��ֵ
	temp&=0XC0;
	temp|=((endy&0X07)<<3)|(sy&0X07);
	SCCB_WR_Reg(0X17,sy>>3);			//����Href��start��8λ
	SCCB_WR_Reg(0X18,endy>>3);			//����Href��end�ĸ�8λ
}
