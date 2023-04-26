/*
 * portconfig.h
 *
 * Created: 10.04.2023 14:43:04
 *  Author: nico
 */ 


#ifndef PORTCONFIG_H_
#define PORTCONFIG_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define R2D PD3

void pin_config(void);
void sys_timer_config(void);
void R2D_config(void);
void R2D_function(uint8_t Hi_thresh, uint8_t Lo_thresh, uint8_t R2D_switch);

ISR(TIMER2_COMP_vect);

#endif /* PORTCONFIG_H_ */