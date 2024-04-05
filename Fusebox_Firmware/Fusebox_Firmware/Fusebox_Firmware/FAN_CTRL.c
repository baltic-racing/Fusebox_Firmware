#include "FAN_CTRL.h"

volatile uint8_t fan_dc;
extern volatile uint8_t temperature;

uint16_t OCM_PU = ( 16000000 / (f_PWM * 8) ) - 1;

uint16_t FAN_PU_SET_PWM(uint16_t temp)
{
	uint16_t DR = 0;		//DR = Dutyratio
	uint16_t DC = 0;		//DC = Dutycycle
	
	if (temp >= TEMP_MAX)
	{
		DR = DR_MAX;
	}
	if (temp <= TEMP_MIN)
	{
		DR = 0;
	}
	if ((temp > TEMP_MIN) && (temp > TEMP_MAX))
	{
		DR = (temp * DR_MAX) / TEMP_MAX;
	}
	
	DC = (DR / 100) * OCM_PU;
	
	return DC;
}

void timer1_config()
{											
	// Fast PWM, Mode 15, Prescaler 8, Inverted Output Mode
	TCCR1A = (1<<WGM11) | (1<<WGM10) | (0<<COM1A1) | (1<<COM1B1);  
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11);
	// Output Compare interrupt flag will be set whenever OCR1A is reached
	TIMSK1 = (1<<OCIE1A);
	OCR1A = OCM_PU;											
	OCR1B = (uint16_t) (OCM_PU / 2);
}

// ISR for the timer 1, updating the duty cycle
ISR(TIMER1_COMPA_vect)
{									
	OCR1B = fan_dc;
}