/*
 * adc_functions.c
 *
 * Created: 06.04.2019 10:58:39
 *  Author: Ole Hannemann
 */ 


#include "adc_functions.h"

// array to store the adc data in
uint16_t adc_values[ADCVALUES]; //Defined in the Header file (2 right now)
// index var to know which adc will come next
uint8_t adc_next = 0;



void adc_config(){
	ADMUX = (1<<REFS0); // AREF = AVcc and PF0 (ADC0) as input defined
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0) | (1<<ADIE);
	// ADEN enables ADC
	// ADIE enables ADC interrupt
	// ADPS (Prescaler) 16
	// see datasheet page 290
	ADCSRA |= (1<<ADSC); //start first conversion
}

void adc_start_conversion(){
	//start next conversion with same config
	ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADSC);
}

ISR(ADC_vect){
	//cli();
	// store ADC result
	adc_values[adc_next] = ADC;// ADCL | (ADCH << 8); //low bit erst ablesen
	adc_next++;
	//adc_values[0] = (ADC*5)/1023;  //cant decide where in the code this should go without testing
	//adc_values[1] = ((ADC*5)/1023)+((10000*(ADC*5)/1023)/2500); //no way this is efficient, needs to be optimized later
	// reset index var
	//sei();
	if(adc_next == ADCVALUES){
		adc_next = 0;
	}
	// select other ADC Input
	ADMUX = (1<<REFS0) | adc_next;

	adc_start_conversion();
	
}

// getter for each adc var
uint16_t adc_get(uint8_t adc){
	
	return adc_values[adc];
}
