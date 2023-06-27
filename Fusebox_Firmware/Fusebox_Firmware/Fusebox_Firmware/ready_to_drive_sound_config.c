/*
 * ready_to_drive_sound_config.c
 *
 * Created: 10.04.2023 16:54:44
 *  Author: adaam
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ready_to_drive_sound_config.h"

unsigned long r2d_length = 0;

uint8_t note_length = 0;
uint8_t current_note = 0;
uint8_t OCR2A_next = 0;
uint8_t song[10] =	{ 10, 16,10, 16,10, 16,10, 16,10, 16/*20, 15,30,  50, 15,70, 15, 15,30,60 *//*160, 200,160, 200,160, 200,160, 200,160, 200*//*32 ,31 ,30 ,29 ,28 ,27 ,28 ,29 ,30 ,31*//*30, 40, 50,40, 30, 40, 50,40,30, 40, 50,40,30, 40, 50,40,30, 40, 50,40,
	30, 40, 50,40,30, 40, 50,40*/};  /*80, 80, 80, 95, 95, 95, 120, 95, 120,
					 160, 160, 142, 95, 80, 80, 80, 80, 95, 120, 160,					//temporary, will change to a simple note progression later
					 160, 160, 120, 120, 120, 120								};*/

uint8_t note_next = 0;

void timer2_config() // timer 1 needs to replace timer 0   //NO NEED FOR GLOBAL CONFIG, TIMER SHOULD ONLY START WHEN THE SOUND IS REQUIRED
{
TCCR2A |= (1<<WGM21);// | (1<<CS22);// | (1<<CS21) | (1<<CS20); //ctc mode 64 pre
	//TCCR0A |= (1<<COM0A1); //clear ocr0a on match
TIMSK2 = (1<<OCIE2A);// Interrupt enabl
	//OCR2A =42 ;		//	  16000000/(2*64*42) = 2976 Hz
	//sei();
		
}

void buzzer_noise(){   //useless as of now (17.05.2023)			
note_length++;

		if (note_length == 5){
			note_length = 0;
			note_next++;
		}
		if (note_next == 10){
			note_next = 0;
		}
}

void R2D(void)
{
	for (uint16_t i = 0; i <= 0xFFF; i++)
	{
		for (uint16_t j = 0; j <= 0x1AF; j++) {}
		PORTD ^= (1 << PD3);	
	}
}

ISR(TIMER2_COMP_vect){ //isr for timer2 
	cli();
	PORTD ^= (1<<PD3);
	OCR2A = song[note_next];
	r2d_length++;
	sei();
}