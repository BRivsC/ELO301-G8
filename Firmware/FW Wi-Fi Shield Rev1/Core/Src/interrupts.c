/*
 * interrupts.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Basti
 */
#include "interrupts.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// Interrupción desde el botón de la Shield
	if (GPIO_Pin == GPIO_BOTON_Pin){
		// Encender LED verde de la placa si detecta interrupción desde el botón
		HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);

		// Leer el sensor cuando reciba la interrupción

	}
}
