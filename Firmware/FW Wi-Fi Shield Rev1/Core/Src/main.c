/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "interrupts.h"
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
enum ESTADO estado=WAIT_ESP;		//Variable que identifica el estado del sistema (FSM).
int BTN=0;							//1 si se resionó el botón, 0 eoc.
enum ESP_ESTADO esp_connect=WAIT;	//resultado de la conexión a internet de la ESP.
enum ESP_ESTADO esp_envio=WAIT; 	//resultado del envío de datos.
volatile char msg;
int responder=0;
int ESP_OK=0;
int ESP_READY=0;
int count=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//enum ESTADO estado=WAIT_ESP;		//Variable que identifica el estado del sistema (FSM).
	int intentos=0;						//Contador de intentos de conexión.
	enum LEDS leds=OFF;					//estado de los leds de estado.
							//1 para ESP lista para trabajar, 0 eoc.
	//int BTN=0;							//1 si se resionó el botón, 0 eoc.
	int reconexion=0;					//1 si se intenta reconexión, 0 eoc.
	chg_led_state(leds);				//al iniciar el sistema se apagan los leds (estado de WAIT_ESP)
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  // Conectarse a ESP


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_UART_Receive_IT(&huart1, (uint8_t*) &msg, 1);
  while (1){
	  switch(estado){
	  	  case WAIT_ESP:
	  		  if(ESP_OK){
		  		  reconexion=0;
	  			  intentos=0;
	  			  esp_connect=FAIL;
	  			  //mandar comando AT para conexión
	  			  setModeToStation();
	  			  if(ESP_READY==1){
	  				estado=ESTABLECER_CONEXION_WI_FI;
	  				ESP_READY=0;
	  			  }
	  			  //HAL_UART_Transmit(&huart1, "test\n", 5, 1000);

	  		  }
			  break;
	  	  case ESTABLECER_CONEXION_WI_FI:
			leds=OFF;
	  		chg_led_state(leds);
	  		  if((intentos<3)&&(esp_connect==FAIL)){		//3 intentos para establecer conexión
	  			  //mandar comando AT para conexión
	  			  setAPcnx();
	  			  intentos+=1;
	  			  if (intentos != 3){
	  				  esp_connect=WAIT;
	  			  }
	  		  }
	  		  else if((esp_connect==OK)&&(reconexion==0)){	//Correcta conexión por primera vez
	  		  	  leds=CONEXION_EXITOSA;
	  			  chg_led_state(leds);
	  			  estado=CONECTADO;
	  		  }
	  		  else if((esp_connect==OK)&&(reconexion==1)){	//Reconexión para volver a intentar el envío de datos
	  			  leds=BUSY;
	  			  chg_led_state(leds);
	  			  esp_envio=WAIT;
	  			  estado=ENVIAR_DATOS;
	  		  }
	  		  else if((esp_connect==FAIL)&&(intentos==3)){	//Falla la conexión, se reinicia la ESP
	  			  //no reset ESP
	  			  ESP_OK=0;
	  			  leds=FALLO_CRITICO;
	  			  chg_led_state(leds);
	  			  estado=FALLO_CONEXION;
	  		  }
	  		  break;
	  	  case CONECTADO:
	  		  if(BTN){//Hay que recolectar y enviar datos
	  			  leds=BUSY;
	  			  chg_led_state(leds);
	  			  //lee sensor
	  			  //enviar datos
	  			  sendSensorData((uint8_t*)"150");
	  			  esp_envio=WAIT;
	  			  BTN=0;
	  			  estado=ENVIAR_DATOS;
	  		  }
	  		  break;
	  	  case ENVIAR_DATOS:
				//if(BTN){
					//Envío datos
					//BTN=0;
				//}
	  		  if(esp_envio==OK){//se enviaron correctamente los datos
	  			  leds=CONEXION_EXITOSA;
	  			  chg_led_state(leds);
	  			  estado=CONECTADO;
	  		  }
	  		  else if(esp_envio==FAIL){//Fallo al enviar datos
	  			  //leds=FALLO_CRITICO;
	  			  //chg_led_state(leds);
	  			  estado=PERDIO_CONEXION;
	  		  }
	  		  
	  		  break;
	  	  case PERDIO_CONEXION:
			leds=FALLO_CRITICO;
	  		chg_led_state(leds);
	  		  reconexion=1;
	  		//  leds=OFF;
	  		//  chg_led_state(leds);
	  		  esp_connect=WAIT;
	  		  intentos=0;
	  		  estado=ESTABLECER_CONEXION_WI_FI;

	  		  break;
	  	  case FALLO_CONEXION:
			HAL_Delay(1000);
			//reset ESP
			resetModule();
			estado=WAIT_ESP;
			/*	
	  		  if(ESP_OK){//Se reseteó correctamente la ESP
	  			  leds=OFF;
	  			  chg_led_state(leds);
	  			  estado=WAIT_ESP;
	  		  } */
	  		break;
			

	  };
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
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
