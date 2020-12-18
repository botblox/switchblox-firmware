/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

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
uint8_t Has_Stopped(void);
uint8_t Is_Erase(void);
void Store_Temp_Command(void);
void Write_Command_To_IC(void);
uint8_t Save_Commands_To_Eeprom(void);
void Erase_Eeprom_Addr(uint32_t Eeprom_ADdress);
void Write_Eeprom_Addr(uint32_t Eeprom_Address, uint32_t Data);
void Read_Eeprom_Data(void);
void Configuration_From_Eeprom(void);
uint8_t Erase_Eeprom_All(void);
void Send_Error_Via_Uart(void);
void Send_Success_Via_Uart(void);
void Blue_Light(void);
void Red_Light(void);
void Green_Light(void);
void White_Light(void);
//void JumpToSystemBootloader(void);


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_BLUE_Pin GPIO_PIN_14
#define LED_BLUE_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_1
#define LED_RED_GPIO_Port GPIOA
#define MIIM_MDC_Pin GPIO_PIN_4
#define MIIM_MDC_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_7
#define LED_GREEN_GPIO_Port GPIOA
#define MIIM_MDIO_Pin GPIO_PIN_10
#define MIIM_MDIO_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
