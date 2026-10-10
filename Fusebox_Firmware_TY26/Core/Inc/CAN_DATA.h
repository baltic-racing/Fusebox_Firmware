/*
 * CAN_DATA.h
 *
 *  Created on: 07.10.2026
 *      Author: Lilly
 */

#ifndef CAN_DATA_H_
#define CAN_DATA_H_

#include <stdint.h>

void CAN_DATA_Init(void);


void CAN_DATA_SendFusebox0(uint16_t bat_sense_mV,
                          uint16_t board_voltage_mV,
                          uint16_t sdc_status);
void CAN_DATA_SendTsacPWM(void);
void CAN_DATA_SendCurrentSense(void);
#endif /* CAN_DATA_H_ */
