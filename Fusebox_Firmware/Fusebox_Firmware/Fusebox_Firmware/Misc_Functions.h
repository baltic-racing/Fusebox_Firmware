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
ISR(TIMER0_COMP_vect);

//macros
#define TIME_PASSED_10_MS	((sys_time - time_old) > 10)
#define TIME_PASSED_100_MS	(time_old_100ms >= 100)
#endif /* MISC_FUNCTIONS_H_ */