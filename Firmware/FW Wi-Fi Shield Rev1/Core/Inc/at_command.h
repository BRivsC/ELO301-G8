/*
 * at-command.h
 *
 *  Created on: Nov 10, 2023
 *      Author: oscarillo
 */

#ifndef INC_AT_COMMAND_H_
#define INC_AT_COMMAND_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"

#define CWMODE 			"AT+CWMODE=1\r\n"
#define RST				"AT+RST\r\n"

#define FIXED_AP		1
#define CWJAP			"AT+CWJAP=\"Yaldy21\",\"12345678\"\r\n"


#define HTTPCLIENT		"AT+HTTPCLIENT=2,0,"
#define HTTPURL			"https://api.thingspeak.com/update?api_key=GZRNUT0P1NZ465CE&field1="
#define HTTPEND			",,,2\r\n"

void setModeToStation(void);

#ifdef FIXED_AP
void setAPcnx(void);
#else
void setRouter(uint8_t* name, uint8_t * pWord);
#endif

void sendSensorData(uint8_t* data);

void resetModule(void);

#endif /* INC_AT_COMMAND_H_ */
