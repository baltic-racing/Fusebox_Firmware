/*
 * cooling_control.h
 *
 *  Created on: 07.10.2026
 *      Author: Lilly
 */

#ifndef COOLING_CONTROL_H_
#define COOLING_CONTROL_H_

#include <stdint.h>
#include "main.h"

void COOLING_CONTROL_Update(void);
void COOLING_CONTROL_Startup(uint32_t now);

void TSAC_PWM_Init(void);
void TSAC_PWM_TimerElapsed(TIM_HandleTypeDef *htim);
uint8_t TSAC_PWM_IsEnabled(void);
uint8_t TSAC_PWM_GetDuty(void);
uint32_t TSAC_PWM_GetPulseCount(void);
#endif /* SRC_COOLING_CONTROL_H_ */
