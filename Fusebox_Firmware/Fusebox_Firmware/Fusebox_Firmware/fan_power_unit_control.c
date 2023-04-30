/*
 * fan_power_unit_control.c
 *
 * Created: 10.04.2023 15:52:18
 *  Author: adaam
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void fan_power_unit_control(){
	
}

void timer1_config(){
TCCR0A = (1<<WGM11) | (1<<WGM10) | (1<<COM1A1) | (1<<COM1A0) | (1<<CS10);
TIMSK1 = (1<<OCIE1A);
OCR1A = 10;


// WGM1[1:0]	= 3;
// COM1[1:0]	= 3;
// CS1[2:0]	= 2;
}

ISR(TIMER1_COMPA_vect){
OCR1 = 150;
}