/*
 * funciones.h
 *  Created on: Nov 10, 2023
 *      Author: tomas
 */

#ifndef INC_FUNCIONES_H_
#define INC_FUNCIONES_H_
#include "main.h"
/**
 * @brief Changes LED's state.
 *
 * Changes the LED's state based on the enum value of the variable leds.
 *
 * @param[in] leds enum value associated to one FSM state.
 * @return void.
 *
 */
void chg_led_state(enum LEDS); //Cambiar el estado de los leds.


#endif /* INC_FUNCIONES_H_ */
