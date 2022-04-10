/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "GUI.h"
#include "GPIOusePin_InLL.h"
#include "lcd.h"
#include "ov7670.h"
#include "sccb.h"
#include "test.h"
#include "keyboard.h"
#include "ds18b20.h"
#include "hcsr04.h"
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
extern unsigned char ov_sta;
int flag=0;
float	Acoustic_velocity=0;
void delay_ustest(unsigned long int t)
{
	LL_TIM_SetCounter(TIM1, 0);
	LL_TIM_EnableCounter(TIM1);
	while(LL_TIM_GetCounter(TIM1) <= t);
}
void camera_refresh(void)
{
//	unsigned char showbuff3={"\0"};
	unsigned long int j;
 	unsigned int color;
	if(ov_sta)//��֡�жϸ��£�
	{
//		LCD_direction(1);//		LCD_Display_Dir(1);
//		LCD_SetWindows(0,(lcddev.height-240)/2,320-1,240-1);
		LCD_SetWindows(0,0,320-1,240-1);//����ʾ�������õ���Ļ����
//		LCD_SetWindows(0,0,280-1,240-1);
//		LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);

		OV7670_RRST_0;				//��ʼ��λ��ָ��
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST_1;				//��λ��ָ�����??????????????????
		OV7670_RCK_H;

		for(j=0;j<76800;j++)   //���ַ�ʽ�����TFT�ڲ���ʾ������ƼĴ����? �ٶȽϿ�320*240
//		for(j=0;j<67200;j++)  //280*240			搭配SETWINDOW 320 240,240少了�???????部分�???????320完整显示		实际�???????320*210
		{
			OV7670_RCK_L;
			color=GPIOD->IDR&0XFF00;	//������
			OV7670_RCK_H;
//			color<<=8;//高八�??????????????
			OV7670_RCK_L;
			color|=(GPIOD->IDR&0XFF00)>>8;	//������
			OV7670_RCK_H;
//			LCD_WriteData_Color(color);
			Lcd_WriteData_16Bit(color);
//			Lcd_WriteData_16Bit_OV(color);
		}
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8);
 		ov_sta=0;					//����֡�жϱ��??????????????????
//		ov_frame++;  //ZHEN SHU XIANG GUAN ,XU YAO PEI HE TIMER JI SUAN
// 		LCD_direction(0);//LCD_Display_Dir(0);

	}
}
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
  unsigned char showbuff[30]={"\0"};
  unsigned char showbuff1[30]={"\0"};
  unsigned char showbuff2[30]={"\0"};
  unsigned char keynum=0;
  short Temperature=0;

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  LL_SPI_Enable(SPI1);
  LL_SPI_EnableDMAReq_RX(SPI1);
  LL_SPI_EnableDMAReq_TX(SPI1);
  LL_SPI_DMA_GetRegAddr(SPI1);
  LL_TIM_OC_SetCompareCH3(TIM4,0);//PWM RESET
  LL_TIM_OC_SetCompareCH4(TIM4,0);
  LCD_Init();
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_8);
  DS18B20_Init();
  float length=0;
  int v=0,i=0;

//  sprintf(showbuff,"lenth=%d \n",v);
//  HAL_UART_Transmit(&huart1, showbuff, 30, 200);






  //**touch and keyboard		show Temperature and	Acoustic_velocity

  TP_Init();
  Temperature=DS18B20_Get_Temp();//小数在个�??????
  Acoustic_velocity=(float)Temperature*0.0607+331.4;//0.607*0.1
	      sprintf(showbuff,"Temperature Value: %d.%d\n",Temperature/10,Temperature%10);			//successfully
//	      HAL_UART_Transmit(&huart1, showbuff, 30, 200);
//	      LL_mDelay(100);
	      sprintf(showbuff1,"Acoustic velocity value:%.1f\n",Acoustic_velocity);
//	      HAL_UART_Transmit(&huart1, showbuff1,30, 200);
  LCD_ShowString(0, 0, 16, showbuff, 1);
  LCD_ShowString(0, 17, 16, showbuff1, 1);
//
  Load_keyboard(0, 170, key_menu);
  keynum=GET_NUM();
//    sprintf(showbuff,"NUM: %d\n",keynum);			//successfully	only once	enter ed go
//    HAL_UART_Transmit(&huart1, showbuff, 30, 200);
//    LL_mDelay(100);


//  for(i=0;i<=3;i++)
//  {
////	  length += Hcsr04GetLength(i);
//	  sprintf(showbuff2,"lenth%d=%.1f \n", i,Hcsr04GetLength(i));
//	  LCD_ShowString(0, 34+i*17, 16, showbuff2, 1);
//  }
//  v=length/4;
//  length=0;
//  HAL_UART_Transmit(&huart1, showbuff, 30, 200);

//  i=1;
//  	  sprintf(showbuff2,"lenth%d=%.1f \n", i,Hcsr04GetLength(i));
//  	  LCD_ShowString(0, 34+i*17, 16, showbuff2, 1);


//  gui_circle(50, 50, 1, 25, 1);
//  SCCB_SDA_IN();
//  SCCB_SDA_OUT();

  // **摄像头模�???????
    OV7670_Init();
  //    int ov7670Init=OV7670_Init();
  //    sprintf(showbuff,"ov7670init: %u\n",ov7670Init);
  //    HAL_UART_Transmit(&huart1, showbuff, 30, 200);
  //    LL_mDelay(100);
//    LL_mDelay(1500);
    OV7670_Light_Mode(0);
    OV7670_Color_Saturation(2);
    OV7670_Brightness(2);
    OV7670_Contrast(2);
    OV7670_Special_Effects(0);
//  LCD_direction(1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


//	  Touch_Test();		//触摸屏手写测�???????




//	  camera_refresh();//camera缓存�???????



//	  LL_GPIO_TogglePin(GPIOC, 13);
//	  GPIOwritePin(GPIOC, 13, 1);
//	  LL_mDelay(500);
//	  GPIOwritePin(GPIOC, 13, 0);
//	  LL_mDelay(500);
//	  LCD_Clear(YELLOW);
//	  LCD_Clear(RED);
//	  LCD_Clear(BLUE);
//	  GPIOwritePin(GPIOB, 6, 1);
//	  SCCB_SCL_1;
//	  LL_mDelay(500);
//	  SCCB_SDA_1;
//	  delay_ustest(50000);
////	  GPIOwritePin(GPIOB, 6, 0);
////	  SCCB_SCL_0;
//	  SCCB_SDA_0;
//	  delay_ustest(50000);
//	  LL_mDelay(500);




	  //*HCSR04		4 ge
//	  LL_mDelay(100);
	  for(i=0;i<=3;i++)
	  {
		  length += Hcsr04GetLength(i);

	  }

	  v=length/4;
	  sprintf(showbuff2,"lenth=%d \n",v);
	  LCD_ShowString(0, 34, 16, showbuff2, 0);
//	  HAL_UART_Transmit(&huart1, showbuff, 30, 200);

	  length=0;


	  //*HCSR04    1 GE

//	  LL_mDelay(100);

//	  length = Hcsr04GetLength(i);

//	  v=length;
//	  sprintf(showbuff,"lenth=%d \n",v);
//	  HAL_UART_Transmit(&huart1, showbuff, 30, 200);

//	  length=0;
//	  v=0;
	  //*



	  //PWM TEST
//	  LL_TIM_OC_SetCompareCH4(TIM4, 999);		//3.28V
//	  LL_TIM_OC_SetCompareCH3(TIM4, 500);		//1.67V



//	  LL_TIM_OC_SetCompareCH3(TIM4, 150);


	  if(v>=keynum)
	  {
		  LL_TIM_OC_SetCompareCH3(TIM4,250);
		  LL_TIM_OC_SetCompareCH4(TIM4,250);
	  }
	  if(v<keynum)
	  {
		  LL_TIM_OC_SetCompareCH3(TIM4,0);
		  LL_TIM_OC_SetCompareCH4(TIM4,0);
		  LCD_direction(1);
		  while(1)
		  {

			  camera_refresh();
		  }
	  }




  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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
