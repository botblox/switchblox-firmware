/*
 * miim_library.c
 *
 *  Created on: Dec 14, 2020
 *      Author: AaronElijah
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


void GPIO_SET_MDIO_MODE_INPUT() {
	/* 
	Sets MDIO pin to Floating Input mode. All other GPIO pins (incl. MDC) remain as Output PP
	Parameters:
		void
	Returns:
		void
	*/
	// Set MIDO pin to it's default status with HAL_GPIO_DeInit
	HAL_GPIO_DeInit(MIIM_MDIO_GPIO_Port, MIIM_MDIO_Pin);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
 	__HAL_RCC_GPIOA_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|MIIM_MDC_Pin|LED_GREEN_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin : LED_BLUE_Pin */
	  GPIO_InitStruct.Pin = LED_BLUE_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(LED_BLUE_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : LED_RED_Pin MIIM_MDC_Pin LED_GREEN_Pin */
	  GPIO_InitStruct.Pin = LED_RED_Pin|MIIM_MDC_Pin|LED_GREEN_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : MIIM_MDIO_Pin */
	  GPIO_InitStruct.Pin = MIIM_MDIO_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(MIIM_MDIO_GPIO_Port, &GPIO_InitStruct);

}

void GPIO_SET_MDIO_MDC_MODE_INPUT() {
	/* 
	Sets MDIO and MDC pins to Floating Input mode. All other GPIO pins remain as Output PP
	Parameters:
		void
	Returns:
		void
	*/
	// Set MIDO pin to it's default status with HAL_GPIO_DeInit
	HAL_GPIO_DeInit(MIIM_MDIO_GPIO_Port, MIIM_MDIO_Pin);

	// Set MDC pin to its default status with HAL_GPIO_Deinit
	HAL_GPIO_DeInit(MIIM_MDC_GPIO_Port, MIIM_MDC_Pin);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
 	__HAL_RCC_GPIOA_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_GREEN_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin : LED_BLUE_Pin */
	  GPIO_InitStruct.Pin = LED_BLUE_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(LED_BLUE_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : LED_RED_Pin MIIM_MDC_Pin LED_GREEN_Pin */
	  GPIO_InitStruct.Pin = LED_RED_Pin|LED_GREEN_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : MIIM_MDIO_Pin */
	  GPIO_InitStruct.Pin = MIIM_MDIO_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(MIIM_MDIO_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : MIIM_MDC_Pin */
	  GPIO_InitStruct.Pin = MIIM_MDC_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(MIIM_MDC_GPIO_Port, &GPIO_InitStruct);
}

void GPIO_SET_MODE_NORMAL() {
	/* 
	Sets all GPIO pins to output (including MDIO and MDC pin)
	Parameters:
		void
	Returns:
		void
	*/
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


void _MIIM_DRIVER_CLOCK_PULSE() {
	/* 
	A clock cycle
	Parameters:
		void
	Returns:
		void
	*/
	HAL_GPIO_WritePin(GPIOA, MIIM_MDC_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, MIIM_MDC_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
}

void _MIIM_DRIVER_START() {
	/* 
	Write the start condition. Start with arbitrary preamble of clock cycles, following by LOW -> HIGH 
	on MDIO pin
	Parameters:
		void
	Returns:
		void
	*/
	// Preamble
	for (uint8_t i=0; i<5; ++i) {
		_MIIM_DRIVER_CLOCK_PULSE();
	}

	// Start clock
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
	_MIIM_DRIVER_CLOCK_PULSE();
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	_MIIM_DRIVER_CLOCK_PULSE();
}

void _MIIM_DRIVER_OP_CODE_READ() {
	/*
	Write the OP READ code. HIGH -> LOW on MDIO (2 clock pulses)
	Parameters:
		void
	Returns:
		void
	*/
	// Data = 0b10
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	_MIIM_DRIVER_CLOCK_PULSE();
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
	_MIIM_DRIVER_CLOCK_PULSE();
}

void _MIIM_DRIVER_OP_CODE_WRITE() {
	/* 
	Write the OP WRITE code. LOW -> HIGH on MDIO (2 clock pulses)
	Parameters:
		void
	Returns:
		void
	*/
	// Data = 0b01
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
	_MIIM_DRIVER_CLOCK_PULSE();
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	_MIIM_DRIVER_CLOCK_PULSE();
}

void _MIIM_DRIVER_PHY_REG_OUTPUT(uint8_t PHY, uint8_t REG) {
	/*
    Write PHY and REG 5 bit addresses to MDIO pin
    Parameters:
		PHY (uint8_t):The SMI PHY address of the register. Ranges from
					  0b00000-0b11111
        REG (uint8_t):The SMI REG address of the register. Ranges from
					  0b00000-0b11111
    Returns:
        void
    */
	// Send the PHY address first
	for (uint8_t bitnum = 0; bitnum <= 4; ++bitnum) {
		if ((PHY & (1 << (4-bitnum))) == 0) {
			HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
		} else {
			HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
		}
		_MIIM_DRIVER_CLOCK_PULSE();
	}

	// Send the REG address first
	for (uint8_t bitnum = 0; bitnum <= 4; ++bitnum) {
		if ((REG & (1 << (4-bitnum))) == 0) {
			HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
		} else {
			HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
		}
		_MIIM_DRIVER_CLOCK_PULSE();
	}
}

void _MIIM_DRIVER_TA_WRITE() {
	/*
    Write turnaround bits for WRITE before writing data. The Turnaround bits for write are the same as the op READ code.
    Parameters:
		void
    Returns:
        void
    */
	_MIIM_DRIVER_OP_CODE_READ();
}

void _MIIM_DRIVER_TA_READ() {
	/*
    Write turnaround bits for READ before reading data. Outputs two clock cycles on MDC with MDIO
	set to floating and LOW respectively.
    Parameters:
		void
    Returns:
        void
    */
	// The TA bits for read
	GPIO_SET_MDIO_MODE_INPUT();
	_MIIM_DRIVER_CLOCK_PULSE();
	GPIO_SET_MODE_NORMAL();
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
	_MIIM_DRIVER_CLOCK_PULSE();
}

void _MIIM_DRIVER_WRITE_DATA(uint16_t data) {
	/*
    Write 2 bytes on MDIO pin. Assume MDIO pin is set to Output mode before writing.
    Parameters:
		data (uint16_t): two bytes to write to MDIO pin
    Returns:
        void
    */
	for (uint8_t bitnum = 0; bitnum <= 15; ++bitnum) {
		if ((data & (1<<(15-bitnum))) == 0) {
			HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
		} else {
			HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
		}
		_MIIM_DRIVER_CLOCK_PULSE();
	}
	// reset clock and data
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, MIIM_MDC_Pin, GPIO_PIN_RESET);
}

uint16_t _MIIM_DRIVER_READ_DATA() {
	/*
    Read 2 bytes on MDIO pin. Configure MDIO pin to Input mode before reading 2 bytes
    Parameters:
		void
    Returns:
        uint16_t
    */
	GPIO_SET_MDIO_MODE_INPUT();
	uint16_t data = 0;
	for (uint8_t bitnum = 0; bitnum <= 15; ++bitnum) {
		data = data + (HAL_GPIO_ReadPin(GPIOA, MIIM_MDIO_Pin) << (15-bitnum));
		_MIIM_DRIVER_CLOCK_PULSE();
	}
	GPIO_SET_MODE_NORMAL();
	// Reset clock and data
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, MIIM_MDC_Pin, GPIO_PIN_RESET);
	return data;
}



void MIIM_DRIVER_WRITE(uint8_t PHY, uint8_t REG, uint16_t DATA) {
	/*
    Outputs register data to PHY and REG addresses.
    Parameters:
		PHY (uint8_t):The SMI PHY address of the register. Ranges from
					  0b00000-0b11111
        REG (uint8_t):The SMI REG address of the register. Ranges from
					  0b00000-0b11111
       	DATA (uint16_t): The data to be send to the PHY register
    Returns:
        void
    */
	// Write the preamble + start code
	_MIIM_DRIVER_START();

	// op code
	_MIIM_DRIVER_OP_CODE_WRITE();

	// write PHY and REG
	_MIIM_DRIVER_PHY_REG_OUTPUT(PHY, REG);

	// TA bits
	_MIIM_DRIVER_TA_WRITE();

	// write data
	_MIIM_DRIVER_WRITE_DATA(DATA);

}

uint16_t MIIM_DRIVER_READ(uint8_t PHY, uint8_t REG) {
	/*
	Reads 2 bytes from PHY and REG address.
	Parameters:
		PHY (uint8_t):The SMI PHY address of the register. Ranges from
					  0b00000-0b11111
        REG (uint8_t):The SMI REG address of the register. Ranges from
					  0b00000-0b11111
	 Returns:
	    uint16_t
	*/
	// Preamble + start code
	_MIIM_DRIVER_START();

	// op code
	_MIIM_DRIVER_OP_CODE_READ();

	// write PHY and REG
	_MIIM_DRIVER_PHY_REG_OUTPUT(PHY, REG);

	// TA bits
	_MIIM_DRIVER_TA_READ();

	// read data
	uint16_t data = _MIIM_DRIVER_READ_DATA();

	return data;
}
