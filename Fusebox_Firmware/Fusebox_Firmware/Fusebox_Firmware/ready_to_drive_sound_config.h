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
ISR(TIMER2_COMP_vect);

#endif /* READY_TO_DRIVE_SOUND_CONFIG_H_ */