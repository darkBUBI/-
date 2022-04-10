/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DS18B20_Pin LL_GPIO_PIN_2
#define DS18B20_GPIO_Port GPIOE
#define TOUCH_CS_Pin LL_GPIO_PIN_13
#define TOUCH_CS_GPIO_Port GPIOC
#define TOUCH_PEN_Pin LL_GPIO_PIN_0
#define TOUCH_PEN_GPIO_Port GPIOC
#define TOUCH_DOUT_Pin LL_GPIO_PIN_1
#define TOUCH_DOUT_GPIO_Port GPIOC
#define TOUCH_TDIN_Pin LL_GPIO_PIN_2
#define TOUCH_TDIN_GPIO_Port GPIOC
#define TOUCH_TCLK_Pin LL_GPIO_PIN_3
#define TOUCH_TCLK_GPIO_Port GPIOC
#define RS_Pin LL_GPIO_PIN_0
#define RS_GPIO_Port GPIOA
#define RST_Pin LL_GPIO_PIN_1
#define RST_GPIO_Port GPIOA
#define CS_Pin LL_GPIO_PIN_2
#define CS_GPIO_Port GPIOA
#define OV7670_CS_Pin LL_GPIO_PIN_15
#define OV7670_CS_GPIO_Port GPIOB
#define OV7670_D0_Pin LL_GPIO_PIN_8
#define OV7670_D0_GPIO_Port GPIOD
#define OV7670_D1_Pin LL_GPIO_PIN_9
#define OV7670_D1_GPIO_Port GPIOD
#define OV7670_D2_Pin LL_GPIO_PIN_10
#define OV7670_D2_GPIO_Port GPIOD
#define OV7670_D3_Pin LL_GPIO_PIN_11
#define OV7670_D3_GPIO_Port GPIOD
#define OV7670_D4_Pin LL_GPIO_PIN_12
#define OV7670_D4_GPIO_Port GPIOD
#define OV7670_D5_Pin LL_GPIO_PIN_13
#define OV7670_D5_GPIO_Port GPIOD
#define OV7670_D6_Pin LL_GPIO_PIN_14
#define OV7670_D6_GPIO_Port GPIOD
#define OV7670_D7_Pin LL_GPIO_PIN_15
#define OV7670_D7_GPIO_Port GPIOD
#define OV7670_RRST_Pin LL_GPIO_PIN_6
#define OV7670_RRST_GPIO_Port GPIOC
#define OV7670_RCK_Pin LL_GPIO_PIN_7
#define OV7670_RCK_GPIO_Port GPIOC
#define OV7670_WREN_Pin LL_GPIO_PIN_8
#define OV7670_WREN_GPIO_Port GPIOC
#define OV7670_WRST_Pin LL_GPIO_PIN_9
#define OV7670_WRST_GPIO_Port GPIOC
#define OV7670_VSYNC_Pin LL_GPIO_PIN_8
#define OV7670_VSYNC_GPIO_Port GPIOA
#define OV7670_VSYNC_EXTI_IRQn EXTI9_5_IRQn
#define Echo0_Pin LL_GPIO_PIN_0
#define Echo0_GPIO_Port GPIOD
#define Trig0_Pin LL_GPIO_PIN_1
#define Trig0_GPIO_Port GPIOD
#define Echo1_Pin LL_GPIO_PIN_2
#define Echo1_GPIO_Port GPIOD
#define Ttig1_Pin LL_GPIO_PIN_3
#define Ttig1_GPIO_Port GPIOD
#define Echo2_Pin LL_GPIO_PIN_4
#define Echo2_GPIO_Port GPIOD
#define Trig2_Pin LL_GPIO_PIN_5
#define Trig2_GPIO_Port GPIOD
#define Echo3_Pin LL_GPIO_PIN_6
#define Echo3_GPIO_Port GPIOD
#define Trig3_Pin LL_GPIO_PIN_7
#define Trig3_GPIO_Port GPIOD
#define SCCB_SCL_Pin LL_GPIO_PIN_6
#define SCCB_SCL_GPIO_Port GPIOB
#define SCCB_SDA_Pin LL_GPIO_PIN_7
#define SCCB_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
