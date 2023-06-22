/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ad9833.h"
#include "ads1115i2c.h"
#include "scan.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

unsigned long int PinDian[40]={0};	//粗扫
 long int FuDu[40]={0};
 long int XiangWei[40]={0};

unsigned long int PinDianL1[40]={0};//第一次扫到最低点
unsigned long int FuDuL1[40]={0};
unsigned long int XiangWeiL1[40]={0};

unsigned long int PinDianH1[40]={0};//第一次扫到最高点
unsigned long int FuDuH1[40]={0};
unsigned long int XiangWeiH1[40]={0};

unsigned long int PinDianL2[40]={0};//第二次扫到最低点
unsigned long int FuDuL2[40]={0};
unsigned long int XiangWeiL2[40]={0};

unsigned long int PinDianH2[40]={0};//第二次扫到最高点
unsigned long int FuDuH2[40]={0};
unsigned long int XiangWeiH2[40]={0};

unsigned long int MaxPL;
unsigned long int MaxFD;
unsigned long int MaxXW;

unsigned long int MinPL;
unsigned long int MinFD;
unsigned long int MinXW;

int PinDianDuan_1L[10]={0};
int PinDianDuan_2L[10]={0};

int PinDianDuan_1H[10]={0};
int PinDianDuan_2H[10]={0};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  int i=2,j=0;
  double fre=1000;
  unsigned  char showbuff[50]={"0"};
//  ads1115_config_register(hi2c1,0x01,CONFIG_REG_H,CONFIG_REG_L);
//  for(fre=1000;fre<=200000;)
//  {
//	  AD9833_WaveSeting(fre,0,1,0);	//delay 稳定 20ms
//	  LL_mDelay(20);
//	  freq[i]=fre;
//	  team[i] = ads1115_read_data(hi2c1);	//AD采样�???
//	  while(i>=2 && (team[i] > team[i-1] || team[i] > team[i-2]) )	//�?低点,当前点比前两个点或�?�前�?点的采样值高，则三点之中存在�?低点
//	  {
//		  scan_2(PinDian[40],FuDu[40],XiangWei[40]);
//
//	  }
//
//	  i++;
//	  if(fre<10000)
//		  fre +=1000;
//	  if(fre>=10000)
//		  fre +=10000;
//  }
  PinDianShengCheng_1(PinDian);
  scan(PinDian,FuDu,XiangWei);											//粗扫,1-10k间隔1k,10k-200k间隔10k
//  while(PinDian[j]!=0)
//  {
//	  sprintf(showbuff,"%d=%d\n",j,PinDian[j]);							//PinDianShengCheng_1  success
//	  HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//	  LL_mDelay(50);
//	  j++;
//  }
//  while(PinDian[j]!=0)
//  {
//	 sprintf(showbuff,"%d= %d\n",PinDian[j],FuDu[j]);							//scan frist CuSao test SUCCESS
//  	 HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//  	 LL_mDelay(50);
//  	 j++;
//  }
//
//  while(PinDian[i]!=0)																//i=2,从第三项,�?始遍�?
//  {
//	  if( FuDu[i] > FuDu[i-1] && FuDu[i-1] < FuDu[i-2] )							//�?低点,当前点比前两个点或�?�前�?点的采样值高，则三点之中存在�?低点
//		{
//		  	sprintf(showbuff,"value= %d\n",i-1); PinDian//succeessfully found  14,20
//		  	HAL_UART_Transmit(&huart1, showbuff,15, 200);
//
//			PinDianShengCheng_L1(PinDian[i-2], PinDian[i],PinDianL1);							//通过两个点重新生成新的频道数�?
//			scan(PinDianL1,FuDuL1,XiangWeiL1);							//第一次扫�?低，间隔1k�?
//
//			while(PinDianL1[i]!=0)
//			{
//				if(FuDuL1[i] > FuDuL1[i-1] || FuDuL1[i] > FuDuL1[i-2])
//				{
//					PinDianShengCheng_L2(PinDianL1[i-2], PinDianL1[i]);					//通过两个点重新生成新的频道数�?
//					scan(PinDianL2,FuDuL2,XiangWeiL2);						//第二次扫�?低，间隔100�?
//					if(FuDuL2[i] > FuDuL2[i-1] || FuDuL2[i] > FuDuL2[i-2])
//						{
//							MinFD=FuDuL2[i-1];MinPL=PinDianL2[i-1];MinXW=XiangWeiL2[i-1];
//						}
//				}
//				i++;
//			}
//
//		}
//	  if( FuDu[i] < FuDu[i-1] || FuDu[i] < FuDu[i-2] )							//�?高点,当前点比前两个点或�?�前�?点的采样值低，则三点之中存在�?高点
//		{
//		  	sprintf(showbuff,"value= %d\n",i);	//found range successfully,but it has two
//		  	HAL_UART_Transmit(&huart1, showbuff,15, 200);
//
//			PinDianShengCheng_H1(PinDian[i-2], PinDian[i]);							//通过两个点重新生成新的频道数�?
//			scan(PinDianH1,FuDuH1,XiangWeiH1);							//第一次扫�?高，间隔100�?
//			while(PinDianH1[i]!=0)
//			{
//				if(FuDuH1[i] < FuDuH1[i-1] || FuDuH1[i] < FuDuH1[i-2])
//				{
//					PinDianShengCheng_H2(PinDianH1[i-2], PinDianH1[i]);					//通过两个点重新生成新的频道数�?
//					scan(PinDianH2,FuDuH2,XiangWeiH2);						//第二次扫�?高，间隔100�?
//					if(FuDuH2[i] < FuDuH2[i-1] || FuDuH2[i] < FuDuH2[i-2])
//						{
//							MinFD=FuDuH2[i-1];MinPL=PinDianH2[i-1];MinXW=XiangWeiH2[i-1];
//						}
//				}
//				i++;
//			}
//
//		}
//	  i++;
//	  LL_mDelay(10);
//  }
//
//    while(PinDianL1[j]!=0)
//    {
//  	  sprintf(showbuff,"%d=%d\n",j,PinDianL1[j]);							//PinDianShengCheng_L1  TEST
//  	  HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//  	  LL_mDelay(50);
//  	  j++;
//    }
//
//
//  j=0;//画图
//  while(PinDian[j]!=0)
//  {
//	  sprintf(showbuff,"UartSend('PL(%d,%d,%d,%d,1);\r\n');CheckBus y( );",PinDian[j-1]/1000, 500-(FuDu[j-1]/500), PinDian[j], 500-(FuDu[j]/500));
//	  HAL_UART_Transmit(&huart1,showbuff, 50, 200);
//	  LL_mDelay(10);
//  }

//Find min

  int z=0;
  while(PinDian[i]!=0)			//frist find minPinDian
  {
	  if( FuDu[i] > FuDu[i-1] && FuDu[i-1] < FuDu[i-2] )
	  {
		  PinDianDuan_1L[z]=i-1;//PinDianDuan_1L[0]
		  z++;
	  }
	 i++;
  }
  i=PinDianDuan_1L[0];
//  sprintf(showbuff,"value= %d\n",i); 			//succeessfully 14
//  HAL_UART_Transmit(&huart1, showbuff,15, 200);
  PinDianShengCheng_S(PinDian[i-1],PinDian[i+1],1000,PinDianL1);//good
//  while(PinDianL1[j]!=0)
//  {
//	  sprintf(showbuff,"%d= %d\n",j,PinDianL1[j]);							//success
//	  HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//	  LL_mDelay(50);
// 	  j++;
//  }
  scan(PinDianL1, FuDuL1, XiangWeiL1);//good
//  while(PinDianL1[j]!=0)
//  {
//	  sprintf(showbuff,"%d= %d\n",PinDianL1[j],FuDuL1[j]);							//scan frist xiSao test SUCCESS
//	  HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//	  LL_mDelay(50);
//	  j++;
//   }


  z=0;
  i=0;
  while(PinDianL1[i]!=0)//second find minPinDian
  {
	  if( FuDuL1[i] > FuDuL1[i-1] && FuDuL1[i-1] < FuDuL1[i-2] )
	  {
		  PinDianDuan_2L[z]=i-1;
		  z++;
	  }
	 i++;
  }
  if( FuDuL1[PinDianDuan_2L[0]] < FuDuL1[PinDianDuan_2L[1]] )
	  i=PinDianDuan_2L[0];
  if( FuDuL1[PinDianDuan_2L[0]] > FuDuL1[PinDianDuan_2L[1]] )
	  i=PinDianDuan_2L[1];

//  sprintf(showbuff,"value= %d\n",i); 			//succeessfully :6
//  HAL_UART_Transmit(&huart1, showbuff,15, 200);

  PinDianShengCheng_S(PinDianL1[i-1],PinDianL1[i+1],100,PinDianL2);

//  while(PinDianL2[j]!=0)
//  {
//	  sprintf(showbuff,"%d= %d\n",j,PinDianL2[j]);							//success
//  	  HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//  	  LL_mDelay(50);
//   	  j++;
//  }

  scan(PinDianL2,FuDuL2,XiangWeiL2);

//  while(PinDianL2[j]!=0)
//  {
//	  sprintf(showbuff,"%d= %d\n",PinDianL2[j],FuDuL2[j]);			//second xisao successfully
//	  HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//	  LL_mDelay(50);
//	  j++;
//   }

  i=0;
  while(PinDianL2[i]!=0)//second find minPinDian
  {
	  if( FuDuL2[i] > FuDuL2[i-1] && FuDuL2[i-1] < FuDuL2[i-2] )
	  {
		  MinPL=PinDianL2[i-1];
		  MinFD=FuDuL2[i-1];
		  	 //XiangWei
	  }
	 i++;
  }

//  sprintf(showbuff,"value= %d\n",MinPL); 			//succeessfully :55700
//  HAL_UART_Transmit(&huart1, showbuff,15, 200);





//find max
  z=0;
  i=0;
  while(PinDian[i]!=0)			//frist find maxPinDian
  {
	  if( FuDu[i] < FuDu[i-1] && FuDu[i-1] > FuDu[i-2] )
	  {
		  PinDianDuan_1H[z]=i-1;//
		  z++;
	  }
	 i++;
  }
  i=PinDianDuan_1H[1];

//  sprintf(showbuff,"value= %d\n",i); 			//succeessfully 19
//  HAL_UART_Transmit(&huart1, showbuff,15, 200);

  PinDianShengCheng_S(PinDian[i-1],PinDian[i+1],1000,PinDianH1);

//  while(PinDianH1[j]!=0)
//  {
//	  sprintf(showbuff,"%d= %d\n",j,PinDianH1[j]);							//success   :110k-120k
//  	  HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//  	  LL_mDelay(50);
//   	  j++;
//  }

  scan(PinDianH1, FuDuH1, XiangWeiH1);

//  while(PinDianH1[j]!=0)
//  {
//	  sprintf(showbuff,"%d= %d\n",j,FuDuH1[j]);							//scan frist xiSao test SUCCESS
//	  HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//	  LL_mDelay(50);
//	  j++;
//  }

  z=0;
  i=0;
  while(PinDianH1[i]!=0)//second find minPinDian
  {
  	if( FuDuH1[i] < FuDuH1[i-1] && FuDuH1[i-1] > FuDuH1[i-2] )
  	{
  		PinDianDuan_2H[z]=i-1;
  		z++;
  	}
  i++;
  }
  if( FuDuH1[PinDianDuan_2H[0]] > FuDuH1[PinDianDuan_2H[1]] )
	  i=PinDianDuan_2H[0];
  if( FuDuH1[PinDianDuan_2H[0]] < FuDuH1[PinDianDuan_2H[1]] )
	  i=PinDianDuan_2H[1];

//  sprintf(showbuff,"value= %d\n",i); 			//succeessfully :14
//  HAL_UART_Transmit(&huart1, showbuff,15, 200);

  PinDianShengCheng_S(PinDianH1[i-1],PinDianH1[i+1],100,PinDianH2);

//  while(PinDianH2[j]!=0)
//  {
//  	 sprintf(showbuff,"%d= %d\n",j,PinDianH2[j]);							//success  :113-115K
//     HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//     LL_mDelay(50);
//      j++;
//  }

  scan(PinDianH2,FuDuH2,XiangWeiH2);

  while(PinDianH2[j]!=0)
  {
	  sprintf(showbuff,"%d= %d\n",PinDianH2[j],FuDuH2[j]);			//second xisao successfully
	  HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
	  LL_mDelay(50);
	  j++;
  }

  i=0;
  while(PinDianH2[i]!=0)//
  {
	  if( FuDuH2[i] <= FuDuH2[i-1] && FuDuH2[i-1] >= FuDuH2[i-2] )
	  {
		  MaxPL=PinDianH2[i-1];
		  MaxFD=FuDuH2[i-1];
		  	 //XiangWei
	  }
	 i++;
  }

  sprintf(showbuff,"value= %d\n",MaxPL); 			//succeessfully :
  HAL_UART_Transmit(&huart1, showbuff,15, 200);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//	  HAL_UART_Transmit(&huart1,"Z", 1, 1000);

	  LL_mDelay(1000);


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_SetSystemCoreClock(72000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
