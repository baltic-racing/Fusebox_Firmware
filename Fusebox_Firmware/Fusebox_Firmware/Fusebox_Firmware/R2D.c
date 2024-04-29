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
// set R2D pin high
PORTD |= (1<<PD4);
}
