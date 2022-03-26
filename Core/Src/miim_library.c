/*
 * miim_library.c
 *
 *  Created on: Dec 14, 2020
 *      Author: AaronElijah
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

volatile uint16_t us_timer = 0;
GPIO_InitTypeDef GPIO_InitStruct = {0, 0, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0};

// Allow shorter than 1 ms sleeps; this function takes an argument that represents tens of microseconds.
// The wait time isn't exact, but it should be around 5-15 us * tens_of_us
void MDIO_WAIT(uint16_t tens_of_us)
{
	// It was measured that one run of this loop takes about 5 us (in Release mode) to 8.5 us (in Debug mode)
	for (us_timer = 0; us_timer < tens_of_us; ++us_timer) {}
}

void GPIO_SET_MDIO_MODE_INPUT() {
	// Set MIDO pin to it's default status with HAL_GPIO_DeInit
	HAL_GPIO_DeInit(MIIM_MDIO_GPIO_Port, MIIM_MDIO_Pin);

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
	  // Commented out to shrink program size and fit into the flash memory; these values are already set.
	  //GPIO_InitStruct.Pull = GPIO_NOPULL;
	  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(LED_BLUE_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : LED_RED_Pin MIIM_MDC_Pin LED_GREEN_Pin */
	  GPIO_InitStruct.Pin = LED_RED_Pin|MIIM_MDC_Pin|LED_GREEN_Pin;
	  // Commented out to shrink program size and fit into the flash memory; these values are already set.
	  //GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  //GPIO_InitStruct.Pull = GPIO_NOPULL;
	  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : MIIM_MDIO_Pin */
	  GPIO_InitStruct.Pin = MIIM_MDIO_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  // Commented out to shrink program size and fit into the flash memory; these values are already set.
	  //GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(MIIM_MDIO_GPIO_Port, &GPIO_InitStruct);
}

void GPIO_SET_MDIO_MDC_MODE_INPUT() {
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
	  // Commented out to shrink program size and fit into the flash memory; these values are already set.
	  //GPIO_InitStruct.Pull = GPIO_NOPULL;
	  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(LED_BLUE_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : LED_RED_Pin MIIM_MDC_Pin LED_GREEN_Pin */
	  GPIO_InitStruct.Pin = LED_RED_Pin|LED_GREEN_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  // Commented out to shrink program size and fit into the flash memory; these values are already set.
	  //GPIO_InitStruct.Pull = GPIO_NOPULL;
	  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : MIIM_MDIO_Pin */
	  GPIO_InitStruct.Pin = MIIM_MDIO_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  // Commented out to shrink program size and fit into the flash memory; these values are already set.
	  //GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(MIIM_MDIO_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : MIIM_MDC_Pin */
	  GPIO_InitStruct.Pin = MIIM_MDC_Pin;
	  // Commented out to shrink program size and fit into the flash memory; these values are already set.
	  //GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  //GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(MIIM_MDC_GPIO_Port, &GPIO_InitStruct);
}

void GPIO_SET_MODE_NORMAL() {
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
	// Commented out to shrink program size and fit into the flash memory; these values are already set.
	//GPIO_InitStruct.Pull = GPIO_NOPULL;
	//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_BLUE_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LED_RED_Pin MIIM_MDC_Pin LED_GREEN_Pin MIIM_MDIO_Pin */
	GPIO_InitStruct.Pin = LED_RED_Pin|MIIM_MDC_Pin|LED_GREEN_Pin|MIIM_MDIO_Pin;
	// Commented out to shrink program size and fit into the flash memory; these values are already set.
	//GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	//GPIO_InitStruct.Pull = GPIO_NOPULL;
	//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void _MIIM_DRIVER_CLOCK_PULSE() {
	HAL_GPIO_WritePin(GPIOA, MIIM_MDC_Pin, GPIO_PIN_RESET);
	MDIO_WAIT(1);
	HAL_GPIO_WritePin(GPIOA, MIIM_MDC_Pin, GPIO_PIN_SET);
	MDIO_WAIT(1);
}

void _MIIM_DRIVER_START() {
	// Preamble
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);

	for (uint8_t bitnum = 0; bitnum < 32; ++bitnum) {
		_MIIM_DRIVER_CLOCK_PULSE();
	}

	// Start clock
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
	_MIIM_DRIVER_CLOCK_PULSE();
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	_MIIM_DRIVER_CLOCK_PULSE();
}

void _MIIM_DRIVER_OP_CODE_READ() {
	// Data = 0b10
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	_MIIM_DRIVER_CLOCK_PULSE();
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
	_MIIM_DRIVER_CLOCK_PULSE();
}

void _MIIM_DRIVER_OP_CODE_WRITE() {
	// Data = 0b01
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
	_MIIM_DRIVER_CLOCK_PULSE();
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	_MIIM_DRIVER_CLOCK_PULSE();
}

void _MIIM_DRIVER_PHY_REG_OUTPUT(uint8_t PHY, uint8_t REG) {
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
	// The Turnaround bits for write are the same as the op code
	_MIIM_DRIVER_OP_CODE_READ();
}

void _MIIM_DRIVER_TA_READ() {
	// The TA bits for read
	GPIO_SET_MDIO_MODE_INPUT();
	_MIIM_DRIVER_CLOCK_PULSE();
	GPIO_SET_MODE_NORMAL();
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_RESET);
	_MIIM_DRIVER_CLOCK_PULSE();
}

void _MIIM_DRIVER_WRITE_DATA(uint16_t data) {
	for (uint8_t bitnum = 0; bitnum <= 15; ++bitnum) {
		HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, (data & (1<<(15-bitnum))) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
		_MIIM_DRIVER_CLOCK_PULSE();
	}
	// final clock pulse afterwards
	_MIIM_DRIVER_CLOCK_PULSE();
	// reset clock and data
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, MIIM_MDC_Pin, GPIO_PIN_RESET);
}

uint16_t _MIIM_DRIVER_READ_DATA() {
	GPIO_SET_MDIO_MODE_INPUT();
	uint16_t data = 0;
	for (uint8_t bitnum = 0; bitnum <= 15; ++bitnum) {
		data = data + (HAL_GPIO_ReadPin(GPIOA, MIIM_MDIO_Pin) << (15-bitnum));
		_MIIM_DRIVER_CLOCK_PULSE();
	}
	// final clock pulse afterwards
	_MIIM_DRIVER_CLOCK_PULSE();
	GPIO_SET_MODE_NORMAL();
	// Reset clock and data
	HAL_GPIO_WritePin(GPIOA, MIIM_MDIO_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, MIIM_MDC_Pin, GPIO_PIN_RESET);
	return data;
}



// Define MIIM bit banging functions here
void MIIM_DRIVER_WRITE(uint8_t PHY, uint8_t REG, uint16_t DATA) {
	/*
    Outputs the PHY and REG addresses to the ethernet chip. Writes 2 byte data packet
    to the ethernet chip for that PHY/REG address.
    Parameters:
        PHY (uint8_t):The data to be sent via the MIIM_MDIO pin
        			  values range from 0b00000000-0b00011111
        			  address corresponds to phy address
        REG (uint8_t):The data to be sent via the MIIM_MDIO pin
        			  values range from 0b00000000-0b00011111
        			  address corresponds to reg address
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
	Reads 2 byte data packet from PHY and REG on ethernet chip.
	Parameters:
	    PHY (uint8_t):The data to be sent via the MIIM_MDIO pin
	        			  values range from 0b00000000-0b00011111
	        			  address corresponds to phy address
	    REG (uint8_t):The data to be sent via the MIIM_MDIO pin
	        			  values range from 0b00000000-0b00011111
	        			  address corresponds to reg address
	 Returns:
	    void
	*/
	// Preamble + start code
	_MIIM_DRIVER_START();

	// op code
	_MIIM_DRIVER_OP_CODE_READ();

	// write PHY and REG
	//uint8_t PHY = 0b11111;
	//uint8_t REG = 0b11010;
	_MIIM_DRIVER_PHY_REG_OUTPUT(PHY, REG);

	// TA bits
	_MIIM_DRIVER_TA_READ();

	// read data
	uint16_t data = _MIIM_DRIVER_READ_DATA();

	return data;
}
