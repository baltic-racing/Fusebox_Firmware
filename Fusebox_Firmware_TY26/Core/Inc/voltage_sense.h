#ifndef VOLTAGE_SENSE_H_
#define VOLTAGE_SENSE_H_

#include <stdint.h>

void VOLTAGE_SENSE_Read(void);
void VOLTAGE_SENSE_Update(void);

uint16_t VOLTAGE_SENSE_GetBoardVoltage(void);
uint16_t VOLTAGE_SENSE_GetBatSense(void);

#endif
