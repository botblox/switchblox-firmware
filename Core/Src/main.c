/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "miim_library.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define buffer_size 4
#define stop_condition 100
#define erase_condition 101

#define data_eeprom_base_addr 0x08080000
#define data_eeprom_end_addr 0x080801FF

#define maximum_commands 20

#define data_eeprom_first_byte_mask 255
#define data_eeprom_second_byte_mask 65280
#define data_eeprom_third_byte_mask 16711680
#define data_eeprom_fourth_byte_mask 4278190080
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

/* USER CODE BEGIN PV */
uint8_t Is_Commands_Ready = 0;

uint8_t Error[] = {2};
uint8_t Success[] = {1};

uint8_t Buffer_Tx[buffer_size] = {80,81,82,83};
uint8_t Buffer_Rx[buffer_size];

uint8_t Generic_Index;
uint32_t Current_Eeprom_Addr;

uint8_t Commands_Total[maximum_commands][buffer_size];
uint8_t Commands_Current_Index = 0;

uint8_t PHY;
uint8_t REG;
uint16_t Data;

uint8_t Condition;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
//	HAL_UART_Transmit_DMA(&huart2, Buffer_Tx, buffer_size);
//}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(Is_Erase()) {
		Erase_Eeprom_All();
	} else if(Has_Stopped()){
		Is_Commands_Ready = 1;
	} else {
		Store_Temp_Command();
	}

	HAL_UART_Receive_DMA(&huart2, Buffer_Rx, buffer_size);
}

uint8_t Has_Stopped() {
	uint8_t value_to_check = Buffer_Rx[0];
	switch(value_to_check) {
		case stop_condition:
			return 1;
		default:
			return 0;
	}
	return 0;
}

uint8_t Is_Erase() {
	uint8_t value_to_check = Buffer_Rx[0];
	switch(value_to_check) {
		case erase_condition:
			return 1;
		default:
			return 0;
	}
	return 0;
}

void Store_Temp_Command() {
	for(Generic_Index = 0; Generic_Index < buffer_size; Generic_Index++) {
		Commands_Total[Commands_Current_Index][Generic_Index] = Buffer_Rx[Generic_Index];
	}

	Commands_Current_Index++;
}

void Write_Commands_To_IC() {
	for(uint8_t Cmd_Index = 0; Cmd_Index < maximum_commands; Cmd_Index++) {
		PHY = Commands_Total[Cmd_Index][0];
		REG = Commands_Total[Cmd_Index][1];

		// Test to see if PHY or REG are not acceptable values
		if(PHY < 2 || PHY > 24 || REG < 0 || REG > 32) {
			break;
		}

		// We are going to assume that for now, the data is sent with the smallest byte [0:7] bits first, then [8:15]
		Data = ((uint16_t) Commands_Total[Cmd_Index][3] << 8) | (Commands_Total[Cmd_Index][2]);

		for(Generic_Index = 0; Generic_Index <= 10; Generic_Index++) {
			MIIM_DRIVER_WRITE(PHY, REG, Data);
			HAL_Delay(1);
		}
	}
}


uint8_t Save_Commands_To_Eeprom() {
	uint32_t Current_Eeprom_Addr = data_eeprom_base_addr;
	uint32_t Data_Word;

	if (HAL_FLASHEx_DATAEEPROM_Unlock() == HAL_OK) {
		for(Generic_Index = 0; Generic_Index < maximum_commands; Generic_Index++) {
			// Write to the EEPROM address in multiples of 4 bytes as we are writing a 32 bit word at a time
			Current_Eeprom_Addr += 4;

			Erase_Eeprom_Addr(Current_Eeprom_Addr);

			// Create the 32 bit word from the 4x byte command
			Data_Word = (((uint32_t) Commands_Total[Generic_Index][3] << 24) | ((uint32_t) Commands_Total[Generic_Index][2] << 16) | ((uint32_t) Commands_Total[Generic_Index][1] << 8) | (Commands_Total[Generic_Index][0]));

			Write_Eeprom_Addr(Current_Eeprom_Addr, Data_Word);
		}
		if(HAL_FLASHEx_DATAEEPROM_Lock() == HAL_OK) {
			return 0;
		} else {
			Error_Handler();
			return 1;
		}
	} else {
		Error_Handler();
		return 1;
	}
	HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin);
}

void Erase_Eeprom_Addr(uint32_t Eeprom_Address) {
	if(HAL_FLASHEx_DATAEEPROM_Erase(Eeprom_Address) == HAL_OK) {
		return;
	} else {
		Error_Handler();
	}
}

void Write_Eeprom_Addr(uint32_t Eeprom_Address, uint32_t Data) {
	if(HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, Eeprom_Address, Data) == HAL_OK) {
		return;
	} else {
		Error_Handler();
	}
}

void Read_Eeprom_Data() {
	uint32_t Current_Eeprom_Addr = data_eeprom_base_addr;
	uint32_t Command;

	for(Generic_Index = 0; Generic_Index < maximum_commands; Generic_Index++) {
		Current_Eeprom_Addr += 4;
		Command = *(uint32_t *)(Current_Eeprom_Addr);

		PHY = (uint8_t) (Command & data_eeprom_first_byte_mask);
		REG = (uint8_t) ((Command & data_eeprom_second_byte_mask) >> 8);

		// Check for invalid PHY and REG
		if(PHY < 2 || PHY > 24 || REG < 0 || REG > 32) {
			break;
		}

		Commands_Total[Generic_Index][0] = PHY;
		Commands_Total[Generic_Index][1] = REG;
		Commands_Total[Generic_Index][2] = (uint8_t) ((Command & data_eeprom_third_byte_mask) >> 16);
		Commands_Total[Generic_Index][3] = (uint8_t) ((Command & data_eeprom_fourth_byte_mask) >> 24);
	}
}

void Configuration_From_Eeprom() {
	Read_Eeprom_Data();
	Blue_Light();
	Write_Commands_To_IC();
	Green_Light();

	// Reset each value in the Commands_Total array
	for(Generic_Index = 0; Generic_Index < maximum_commands; Generic_Index++) {
		Commands_Total[Generic_Index][0] = 0;
		Commands_Total[Generic_Index][1] = 0;
		Commands_Total[Generic_Index][2] = 0;
		Commands_Total[Generic_Index][3] = 0;
	}
}

uint8_t Erase_Eeprom_All(void) {
	uint32_t Current_Eeprom_Addr = data_eeprom_base_addr;

	if(HAL_FLASHEx_DATAEEPROM_Unlock() == HAL_OK) {
		for(Generic_Index = 0; Generic_Index < maximum_commands; Generic_Index++) {
			Current_Eeprom_Addr += 4;

			Erase_Eeprom_Addr(Current_Eeprom_Addr);

		}
		if(HAL_FLASHEx_DATAEEPROM_Lock() == HAL_OK) {
			return 0;
		} else {
			Error_Handler();
			return 1;
		}
	} else {
		Error_Handler();
		return 1;
	}

}

void Send_Error_Via_Uart() {
	HAL_UART_Transmit(&huart2, Error, sizeof(Error), 100);
	Red_Light();
}

void Send_Success_Via_Uart() {
	HAL_UART_Transmit(&huart2, Success, sizeof(Success), 100);
	Blue_Light();
}

void Blue_Light() {
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_GREEN_Pin, GPIO_PIN_SET);
}

void Red_Light() {
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_RESET);
}

void Green_Light() {
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_RESET);
}

void White_Light() {
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_GREEN_Pin, GPIO_PIN_RESET);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
//  uint32_t JumpAddress= *(volatile uint32_t *)(0x1FFF0000 + 4);
//  void (* boot_loader)(void) = (void *) JumpAddress;
//  SYSCFG->CFGR1 = 0x1;  //Remap 0x00000000 to System Memory
//  boot_loader();

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
   HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(1000);
  Configuration_From_Eeprom();

  HAL_UART_Receive_DMA(&huart2, Buffer_Rx, buffer_size);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_Delay(1);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(Is_Commands_Ready) {
		  Red_Light();
		  Write_Commands_To_IC();
		  Green_Light();
		  Condition = Save_Commands_To_Eeprom();
		  if(Condition == 0) {
			  // Success
			  Send_Success_Via_Uart();
		  } else if(Condition == 1) {
			  // Failure
			  Send_Error_Via_Uart();
		  }

		  Is_Commands_Ready = 0;
		  Commands_Current_Index = 0;

		  // Reset the LED to emit white light
		  HAL_Delay(500);
		  Green_Light();
	  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|MIIM_MDC_Pin|LED_GREEN_Pin|MIIM_MDIO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_BLUE_Pin */
  GPIO_InitStruct.Pin = LED_BLUE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_BLUE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_RED_Pin MIIM_MDC_Pin LED_GREEN_Pin MIIM_MDIO_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|MIIM_MDC_Pin|LED_GREEN_Pin|MIIM_MDIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
