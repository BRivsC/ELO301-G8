/*
 * interrupts.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Basti
 */

#ifndef INC_INTERRUPTS_H_
#define INC_INTERRUPTS_H_
#include "main.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart);
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_INTERRUPTS_H_ */
