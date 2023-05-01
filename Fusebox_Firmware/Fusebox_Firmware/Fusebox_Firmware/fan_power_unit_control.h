/*
 * fan_power_unit_control.h
 *
 * Created: 10.04.2023 15:52:27
 *  Author: adaam
 */ 


#ifndef FAN_POWER_UNIT_CONTROL_H_
#define FAN_POWER_UNIT_CONTROL_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void timer1_config();
ISR(TIMER1_COMPA_vect);

#endif /* FAN_POWER_UNIT_CONTROL_H_ */