/*
 * interrupts.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Basti
 */
#include "interrupts.h"
#include "defines.h"
#include "funciones.h"
#include "main.h"

#include <stdio.h>
#include <string.h>

#include "usart.h"
#include "tim.h"

extern char msg;
extern int responder;
extern int BTN;
extern enum ESTADO estado;
extern enum ESP_ESTADO esp_connect;	//resultado de la conexión a internet de la ESP.
extern enum ESP_ESTADO esp_envio;
extern int ESP_OK;
extern int ESP_READY;
extern int count;
uint8_t rx_buffer [50];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// Interrupción desde el botón de la Shield
	if ((GPIO_Pin == GPIO_BOTON_Pin) && (estado==CONECTADO)){ //Ante interrupción del botón, cambiar flag BTN a 1 cuando corresponda
		BTN=1;
	}
	HAL_UART_Receive_IT(&huart1, (uint8_t*) &msg, 1);
}


void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
 if(huart->Instance == USART1)
 {
	 rx_buffer[count]=msg;
	 count++;

	 if (strstr(rx_buffer,"WIFI DISCONNECT")!=NULL){
		 //estado=PERDIO_CONEXION;
		 responder=1;
		 count=0;
		 memset(rx_buffer,'\0',sizeof(rx_buffer));
	 }

	 /*if (strstr(rx_buffer,"OK")!=NULL){
		 responder=3;
		count=0;
		memset(rx_buffer,'\0',sizeof(rx_buffer));
	 }*/

	 switch(estado){
	 	 case WAIT_ESP:
	 		if (strstr(rx_buffer,"ready")!=NULL){
	 			ESP_OK=1;
	 			count=0;
	 			memset(rx_buffer,'\0',sizeof(rx_buffer));
	 		}
	 		if (strstr(rx_buffer,"OK")!=NULL){
				ESP_READY=1;
				count=0;
				memset(rx_buffer,'\0',sizeof(rx_buffer));
	 		}

	 		break;
	 	case ESTABLECER_CONEXION_WI_FI:
	 		if (strstr(rx_buffer,"OK")!=NULL){
	 			esp_connect=OK;
				count=0;
				memset(rx_buffer,'\0',sizeof(rx_buffer));
	 		}
	 		else if (strstr(rx_buffer,"ERROR")!=NULL){
	 			esp_connect=FAIL;
	 			//intentos++;
				count=0;
				memset(rx_buffer,'\0',sizeof(rx_buffer));
	 		}
	 		break;
	 	case ENVIAR_DATOS:
			if (strstr(rx_buffer,"OK")!=NULL){
				esp_envio=OK;
				count=0;
				memset(rx_buffer,'\0',sizeof(rx_buffer));
			}
			else if (strstr(rx_buffer,"ERROR")!=NULL){
				esp_envio=FAIL;
				count=0;
				memset(rx_buffer,'\0',sizeof(rx_buffer));
			}
			//no entendí estado de else if (BTN)
			break;
	 	case FALLO_CONEXION:

	 		break;
	 }

/*
	 if (strstr(rx_buffer,"ready")!=NULL){
	 		 responder=2;
	 		 count=0;
	 		 memset(rx_buffer,'\0',sizeof(rx_buffer));
	 	 }
*/

 }
 HAL_UART_Receive_IT(&huart1, (uint8_t*) &msg, 1); //activate UART receive interrupt

}

