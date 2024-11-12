/*
 * Misc_Functions.h
 *
 * Created: 08.04.2023 19:04:28
 *  Author: adaam
 */ 


#ifndef MISC_FUNCTIONS_H_
#define MISC_FUNCTIONS_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void port_config();
void sys_timer_config();
void sys_tick_heart();
void fault_not_detected();
void fault_detected();

int16_t calculate_ac_current(uint16_t limit, uint16_t value);
int16_t calculate_ac_current_sa_R(uint16_t limit, uint16_t value, uint16_t sa);
int16_t calculate_ac_current_sa_L(uint16_t limit, uint16_t value, uint16_t sa);

ISR(TIMER0_COMP_vect);

#endif /* MISC_FUNCTIONS_H_ */