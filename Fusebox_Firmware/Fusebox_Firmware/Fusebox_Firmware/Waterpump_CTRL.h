/*
 * water_pump_control.h
 *
 * Created: 10.04.2023 15:52:59
 *  Author: adaam
 */ 


#ifndef WATER_PUMP_CONTROL_H_
#define WATER_PUMP_CONTROL_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define TEMP_MAX 60
#define TEMP_MIN 35

#define DR_MAX 100

// Calculating the Output Compare Match Value for Power Unit f_PWM
// Formula on Page 129 in Datasheet for 30kHz, 16 MHz and Prescaler = 8
// Edit Prescaler in timer1_config if needed

#define wp_PWM 30000

uint16_t WP_SET_PWM(uint16_t temp);
void timer3_config();


ISR(TIMER3_COMPA_vect);


#endif /* WATER_PUMP_CONTROL_H_ */