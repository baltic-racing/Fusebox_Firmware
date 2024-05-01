#include "R2D.h"
#include <avr/io.h>
#include <avr/interrupt.h>
/*
 * R2D.c
 *
 * Created: 28.04.2024 20:29
 * 
 */ 

void R2D_activation ()
{
	for (uint16_t i = 0; i <= 0xFFF; i++)
	{
		for (uint16_t j = 0; j <= 0x1AF; j++) {}
		PORTD ^= (1 << PD4);
	}
}