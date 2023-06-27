/*
 * ready_to_drive_sound_config.h
 *
 * Created: 10.04.2023 16:54:58
 *  Author: adaam
 */ 


#ifndef READY_TO_DRIVE_SOUND_CONFIG_H_
#define READY_TO_DRIVE_SOUND_CONFIG_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void timer2_config();
void buzzer_noise();
void R2D(void);

ISR(TIMER2_COMP_vect);

//macros

#define START_TIMER_2 (TCCR2A |= (1<<CS22))

#endif /* READY_TO_DRIVE_SOUND_CONFIG_H_ */