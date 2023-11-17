/*
 * at-command.c
 *
 *  Created on: Nov 10, 2023
 *      Author: oscarillo
 */

#include <at_command.h>

/**
  * @brief	Set the WIFI mode to station
  * @note
  * @param	void
  * @retval	void
  */
void setModeToStation(void){
	HAL_UART_Transmit(&huart1, (uint8_t*) CWMODE, strlen(CWMODE), 10);
}
/**
  * @brief	Connect the ESP32 module to the AP (router)
  * @note
  * @param	name		String with Name of the AP
  * @param	pWord		String with Password of the AP
  * @retval	void
  */
#ifdef FIXED_AP
void setAPcnx(void){
	HAL_UART_Transmit(&huart1, (uint8_t*) CWJAP, strlen(CWJAP), 10);
}
#else
void setAPcnx(uint8_t* name, uint8_t * pWord){
	char temp[50];
	sprintf(temp, "%s\"%s\",\"%s\"",CWJAP,name,pWord);
	HAL_UART_Transmit(&huart1, (uint8_t*) temp, strlen(temp), 10);
	//HAL_UART_Transmit(&huart1, (uint8_t*) CWJAP, sizeof(CWJAP), 10);
}
#endif

/**
  * @brief	Set the packet with the necessary data and send
  * @note	Packet structure is following
  * 		AT+HTTPCLIENT=2,0,"https://api.thingspeak.com/update?api_key=GZRNUT0P1NZ465CE&field1=5",,,2
  * @param	sensorData		Pointer to the string that contains the data to send
  * @retval	void
  */
void sendSensorData(uint8_t* sensorData){
	char temp[100];
	memset(temp,0,sizeof(temp));
	sprintf(temp, "%s\"%s%s\"%s", HTTPCLIENT, HTTPURL, sensorData,HTTPEND);
	HAL_UART_Transmit(&huart1, (uint8_t*) temp, strlen(temp), 50);
}

/**
  * @brief	Reset the ESP module
  * @note
  * @param	void
  * @retval	void
  */
void resetModule(void){
	HAL_UART_Transmit(&huart1, (uint8_t*) RST, strlen(RST), 10);
}
