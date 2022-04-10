//#include "system.h"
#include "sccb.h"
#include "stm32f4xx_ll_tim.h"
#include "usart.h"
//#include "SysTick.h"
unsigned char showbuff2[30]={"\0"};
void delay_us(unsigned int t)
{
	LL_TIM_SetCounter(TIM1, 0);
	LL_TIM_EnableCounter(TIM1);
	while(LL_TIM_GetCounter(TIM1) <= t);
	LL_TIM_DisableCounter(TIM1);
	LL_TIM_SetCounter(TIM1, 0);
}

//void SCCB_SDA_OUT(void)
//{
//	LL_GPIO_InitTypeDef GPIO_Init={0} ;
//	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
//	GPIO_Init.Pin = SCCB_SDA_Pin;				 // �˿�����
//	GPIO_Init.Mode = LL_GPIO_MODE_OUTPUT;
//	GPIO_Init.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
//	GPIO_Init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_Init.Pull = LL_GPIO_PULL_NO;
//	LL_GPIO_Init(GPIOB, &GPIO_Init);
//}
//
//void SCCB_SDA_IN(void)
//{
//	LL_GPIO_InitTypeDef  GPIO_Init={0};
//	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
//	GPIO_Init.Pin = SCCB_SDA_Pin;				 // �˿�����
//	GPIO_Init.Mode = LL_GPIO_MODE_INPUT;
//	GPIO_Init.Pull = LL_GPIO_PULL_UP;
// 	LL_GPIO_Init(GPIOB, &GPIO_Init);
//}
 
//��ʼ��SCCB�ӿ�
//CHECK OK
void SCCB_Init(void)
{
// 	GPIO_InitTypeDef  GPIO_InitStructure;
//
//	LL_GPIO_InitTypeDef  GPIO_InitStruct;
// 	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG, ENABLE);

// 	GPIO_InitStruct.Pin = GPIO_PIN_7;				 // �˿�����
// 	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 		 //����
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
// 	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

////
// 	GPIO_InitStruct.Pin = GPIO_PIN_6;				 // �˿�����
// 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 		 //�����
// 	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
// 	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIOwritePin(GPIOB,6,1);//GPIOwritePin(GPIOA,11,1);//GPIO_SetBits(GPIOB,GPIO_Pin_3);						 // �����
//
	GPIOwritePin(GPIOB,7,1);//GPIOwritePin(GPIOA,12,1);//GPIO_SetBits(GPIOG,GPIO_Pin_13);						 // �����
	SCCB_SDA_OUT();
}

//SCCB��ʼ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĸߵ���,ΪSCCB��ʼ�ź�
//�ڼ���״̬��,SDA��SCL��Ϊ�͵�ƽ
void SCCB_Start(void)
{
    SCCB_SDA_1;     //�����߸ߵ�ƽ
    SCCB_SCL_1;	    //��ʱ���߸ߵ�ʱ���������ɸ�����
    delay_us(50);  
    SCCB_SDA_0;
    delay_us(50);	 
    SCCB_SCL_0;	    //�����߻ָ��͵�ƽ��������������Ҫ
}

//SCCBֹͣ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĵ͵���,ΪSCCBֹͣ�ź�
//����״����,SDA,SCL��Ϊ�ߵ�ƽ
void SCCB_Stop(void)
{
    SCCB_SDA_0;
    delay_us(50);	 
    SCCB_SCL_1;
    delay_us(50); 
    SCCB_SDA_1;
    delay_us(50);
}  
//����NA�ź�
void SCCB_No_Ack(void)
{
	delay_us(50);
	SCCB_SDA_1;
	SCCB_SCL_1;
	delay_us(50);
	SCCB_SCL_0;
	delay_us(50);
	SCCB_SDA_0;
	delay_us(50);
}
//SCCB,д��һ���ֽ�
//����ֵ:0,�ɹ�;1,ʧ��.
unsigned char SCCB_WR_Byte(unsigned char dat)
{
	unsigned char j,res;
	//test
	SCCB_SDA_OUT();
	//
	for(j=0;j<8;j++) //ѭ��8�η�������
	{
		if(dat&0x80)SCCB_SDA_1;
		else SCCB_SDA_0;
		dat<<=1;
		delay_us(50);
		SCCB_SCL_1;
		delay_us(50);
		SCCB_SCL_0;
	}			 
	SCCB_SDA_IN();		//����SDAΪ����
	delay_us(50);
	SCCB_SCL_1;			//���յھ�λ,���ж��Ƿ��ͳɹ�
	delay_us(50);
	if(SCCB_READ_SDA)res=1;  //SDA=1����ʧ�ܣ�����1
	else res=0;         //SDA=0���ͳɹ�������0
	SCCB_SCL_0;
	SCCB_SDA_OUT();		//����SDAΪ���
	return res;  
}	 
//SCCB ��ȡһ���ֽ�
//��SCL��������,��������
//����ֵ:����������
unsigned char SCCB_RD_Byte(void)
{
	unsigned char temp=0,j;
	SCCB_SDA_IN();		//����SDAΪ����
	for(j=8;j>0;j--) 	//ѭ��8�ν�������
	{		     	  
		delay_us(50);
		SCCB_SCL_1;
		temp=temp<<1;
		if(SCCB_READ_SDA)temp++; //全1，输出255，为何会全1呢;现在全0了。
		delay_us(50);
		SCCB_SCL_0;
	}	
	SCCB_SDA_OUT();		//����SDAΪ���
	return temp;
} 							    
//д�Ĵ���
//����ֵ:0,�ɹ�;1,ʧ��.
unsigned char SCCB_WR_Reg(unsigned char reg,unsigned char data)
{
	unsigned char res=0;
	SCCB_Start(); 					//����SCCB����
	if(SCCB_WR_Byte(SCCB_ID))res=1;	//д����ID
	delay_us(100);
  	if(SCCB_WR_Byte(reg))res=1;		//д�Ĵ�����ַ
	delay_us(100);
  	if(SCCB_WR_Byte(data))res=1; 	//д����
  	SCCB_Stop();	  
  	return	res;
}		  					    
//���Ĵ���
//����ֵ:�����ļĴ���ֵ
unsigned char SCCB_RD_Reg(unsigned char reg)
{
	unsigned char val=0;
	SCCB_Start(); 				//����SCCB����
	SCCB_WR_Byte(SCCB_ID);		//д����ID
	delay_us(100);	 
  	SCCB_WR_Byte(reg);			//д�Ĵ�����ַ
	delay_us(100);	  
	SCCB_Stop();   
	delay_us(100);	   
	//���üĴ�����ַ�󣬲��Ƕ�
	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID|0X01);	//���Ͷ�����
	delay_us(100);
  	val=SCCB_RD_Byte();		 	//��ȡ����
  	SCCB_No_Ack();
  	SCCB_Stop();
//	  sprintf(showbuff2,"sccb_rd_reg: %u\n",val);
//	  HAL_UART_Transmit(&huart1, showbuff2, 30, 200);
//	  LL_mDelay(100);
  	return val;
}















