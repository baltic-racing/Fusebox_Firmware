/*
 * fan_power_unit_control.h
 *
 * Created: 10.04.2023 15:52:27
 *  Author: adaam
 */ 


#ifndef FAN_POWER_UNIT_CONTROL_H_
#define FAN_POWER_UNIT_CONTROL_H_

#define TEMP_MAX 100
#define TEMP_MIN 5
#include <avr/io.h>
#include <avr/interrupt.h>

void fan_power_unit_PWM_control(uint8_t temperature, uint8_t fan_duty);
void timer1_config();
ISR(TIMER1_COMPA_vect);

#endif /* FAN_POWER_UNIT_CONTROL_H_ */