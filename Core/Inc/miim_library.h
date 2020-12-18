/*
 * miim_library.h
 *
 *  Created on: Dec 14, 2020
 *      Author: AaronElijah
 */

#ifndef INC_MIIM_LIBRARY_H_
#define INC_MIIM_LIBRARY_H_


void GPIO_SET_MDIO_MODE_INPUT();
void GPIO_SET_MDIO_MDC_MODE_INPUT();
void GPIO_SET_MODE_NORMAL();
void _MIIM_DRIVER_CLOCK_PULSE();
void _MIIM_DRIVER_START();
void _MIIM_DRIVER_OP_CODE_READ();
void _MIIM_DRIVER_OP_CODE_WRITE();
void _MIIM_DRIVER_PHY_REG_OUTPUT(uint8_t PHY, uint8_t REG);
void _MIIM_DRIVER_TA_WRITE();
void _MIIM_DRIVER_TA_READ();
void _MIIM_DRIVER_WRITE_DATA(uint16_t data);
uint16_t _MIIM_DRIVER_READ_DATA();
void MIIM_DRIVER_WRITE(uint8_t PHY, uint8_t REG, uint16_t DATA);
uint16_t MIIM_DRIVER_READ(uint8_t PHY, uint8_t REG);

#endif /* INC_MIIM_LIBRARY_H_ */
