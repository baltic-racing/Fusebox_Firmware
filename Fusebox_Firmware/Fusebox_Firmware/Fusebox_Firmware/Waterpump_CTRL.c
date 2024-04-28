#include "Waterpump_CTRL.h"


volatile uint16_t wp_dc;

uint16_t OCM_WP = ( (float)16000000 / ((float)wp_PWM * (float)8) ) - 1;

uint16_t WP_SET_PWM(uint16_t temp)
{
	

	uint16_t DR_WP = 60;		//DR = Dutyratio
	uint16_t DC_WP = 100;		//DC = Dutycycle
	
	/*if (temp >= TEMP_WP_MAX)
	{
		DR_WP = DR_WP_MAX;
	}
	if (temp <= TEMP_WP_MIN)
	{
		DR_WP = 50;
	}
	if ((temp > TEMP_WP_MIN) && (temp < TEMP_WP_MAX))
	*/
	DC_WP = ((float)DR_WP / 100) * (float)OCM_WP;
	
	return DC_WP;
}

void timer3_config()
{
	// Fast PWM, Mode 15, Prescaler 8, Inverted Output Mode
	TCCR3A = (1<<WGM31) | (1<<WGM30) | (0<<COM3A1) | (1<<COM3B1) | (1<<COM0A0);
	TCCR3B = (1<<WGM33) | (1<<WGM32) | (1<<CS31);
	// Output Compare interrupt flag will be set whenever OCR2A is reached
	TIMSK3 = (1<<OCIE3A);
	OCR3A = OCM_WP;
	OCR3B = 1;
}

// ISR for the timer 3, updating the duty cycle
ISR(TIMER3_COMPA_vect)
{
	OCR3B = wp_dc;
}
