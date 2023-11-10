/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32l4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define MESP_EN_Pin GPIO_PIN_0
#define MESP_EN_GPIO_Port GPIOA
#define TX_STM_Pin GPIO_PIN_2
#define TX_STM_GPIO_Port GPIOA
#define RX_STM_Pin GPIO_PIN_3
#define RX_STM_GPIO_Port GPIOA
#define LD4_Pin GPIO_PIN_5
#define LD4_GPIO_Port GPIOA
#define GPIO_BOTON_Pin GPIO_PIN_10
#define GPIO_BOTON_GPIO_Port GPIOB
#define GPIO_BOTON_EXTI_IRQn EXTI15_10_IRQn
#define GPIO_LED_VERDE_Pin GPIO_PIN_7
#define GPIO_LED_VERDE_GPIO_Port GPIOC
#define SENSOR_INT_Pin GPIO_PIN_8
#define SENSOR_INT_GPIO_Port GPIOA
#define SENSOR_INT_EXTI_IRQn EXTI9_5_IRQn
#define SENSOR_SCL_Pin GPIO_PIN_9
#define SENSOR_SCL_GPIO_Port GPIOA
#define SENSOR_SDA_Pin GPIO_PIN_10
#define SENSOR_SDA_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define GPIO_LED_ROJO_Pin GPIO_PIN_6
#define GPIO_LED_ROJO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
