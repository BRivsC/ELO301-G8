/*
 * defines.h
 *
 *  Created on: Nov 10, 2023
 *      Author: tomas
 */

#ifndef INC_DEFINES_H_
#define INC_DEFINES_H_

enum ESTADO{ 	//definición de estados para la FSM.
	WAIT_ESP,		//Esperando a inicialización de ESP ("ready")
	QUERY_CONEXION, 			//
	WAIT_OK_ESP,	//Esperando respuesta a comando AT de modo ("OK")
	ESTABLECER_CONEXION_WI_FI,	//Intentar establecer conexión a interet
	CONECTADO,		//La ESP está conectada a internet
	WAIT_ENVIAR_DATOS, //Espera resultados del envío de datos
	ENVIAR_DATOS,	//La ESP está enviando datos
	PERDIO_CONEXION,//La ESP perdió conexión a internet
	FALLO_CONEXION	//La ESP no logró la conexión a internet
};

enum ESP_ESTADO{//Definición de estados para resultados de acciones de la ESP.
	OK,			//ÉXITO
	FAIL,		//FRACASO
	WAIT		//EN ESPERA
};

enum LEDS{		//Definición de estados para los LEDS(según estado de la FSM).
	CONEXION_EXITOSA,	//Se logró conexión (LED verde ON, LED rojo OFF)
	BUSY,				//ESP enviando datos (LED verde ON, LED rojo ON)
	FALLO_CRITICO,		//No se logró conexión (LED verde OFF, LED rojo ON)
	OFF					//Estados de paso, intentar conexió (LED verde OFF , LED rojo OFF)
};
#endif /* INC_DEFINES_H_ */
