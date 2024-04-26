#include "Waterpump_CTRL.h"


volatile uint16_t wp_dc;

uint16_t OCM_WP = ( (float)16000000 / ((float)wp_PWM * (float)8) ) - 1;

uint16_t WP_SET_PWM(uint16_t temp)
{
	

	uint16_t DR = 100;		//DR = Dutyratio
	uint16_t DC = 100;		//DC = Dutycycle
	
	if (temp >= TEMP_MAX)
	{
		DR = DR_MAX;
	}
	if (temp <= TEMP_MIN)
	{
		DR = 50;
	}
	if ((temp > TEMP_MIN) && (temp < TEMP_MAX))
	
	DC = ((float)DR / 100) * (float)OCM_WP;
	
	return DC;
}

void timer3_config()
{
	// Fast PWM, Mode 15, Prescaler 8, Inverted Output Mode
	TCCR3A = (1<<WGM11) | (1<<WGM10) | (0<<COM1A1) | (1<<COM1B1) | (1<<COM0A0);
	TCCR3B = (1<<WGM13) | (1<<WGM12) | (1<<CS11);
	// Output Compare interrupt flag will be set whenever OCR1A is reached
	TIMSK3 = (1<<OCIE3A);
	OCR3A = OCM_WP;
	OCR3B= 1;
}

// ISR for the timer 3, updating the duty cycle
ISR(TIMER3_COMPA_vect)
{
	OCR3B = wp_dc;
}
