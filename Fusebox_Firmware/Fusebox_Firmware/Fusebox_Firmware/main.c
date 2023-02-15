/*
 * Fusebox_Firmware.c
 *
 * Created: 13.02.2023 11:41:48
 * Author : adaam
 */ 
//attempt 1
// int main(void)
//     DDRB = 00011000;   //PB3 and 4 set to output with the data direction register
//     PORTB = 0x00;  // Initial state - all ports logic 0
//     while (1)
//     {
// 	PORTB |= (1<<PB3);		 // Bit 3 set to 1 (red on)
// 	_delay_ms(250);
// 	PORTB &= ~(1<<PB3);		//bit 3 set to 0 (red off)
// 	PORTB |= (1<<PB4);		//bit 4 set to 1 (blue on)
// 	_delay_ms(250);
// 	PORTB |= (1<<PB3);
// 	PORTB &= ~(1<<PB4);
// 	_delay_ms(250);

//attempt 2 - overflow + interrupt
// DDRB |= (1<<PB4) | (1<<PB3); //0b00011000;   //PB3 and 4 set to output with the data direction register
// // PORTB = 0x00;  // Initial state - all ports logic 0
// TCCR1B = (1<<CS10) | ~(1<<CS11) | (1<<CS12);   //page 139 setup of the clock (counter 1 in control register B)
// TCNT1 = 0;  // utilized counter is the counter 1 therefore TCNT1
// OCR1A = 1; //a OCF1A flag will be set once TCNT1 Reaches this value (page 144), here the value is the clk frequency/1 (approx every 4,16 sec) (TOP of the counter)
// while (1)
// {
// 	while (TIFR1 &(1<< OCF1A) == 0);  // Interrupt requests signals are all visible in the Timer Interrupt Flag Register (TIFRn) (page 114)
// 	PORTB ^= (1<< PB4)  | (1<<PB3);	//toggle with xor
// 	TCNT1 = 0; //set back to 0 in preparation to repeat the process
// 	TIFR1 |= (1<< OCF1A);	// "the OCF0A flag can be cleared by software by writing a logical one to its I/O bit location" page 101
// does not work


//{
	//DDRB = 0xff;//|= (1<<PB3) | (1<<PB4); //ob00111000 (red, blue,)
// 	
// 	DDRB |= (1<<PB2);  nutzlos
// 	PORTB |= (1<<PB2); soll toggeln nicht perma zu 1 setzen?
//	PORTB &= ~(1<<PB2);
//======================================================================================================== toggler
//      while (1)
//      {
// 	 PORTB ^= (1<<PB3) ; //toggle red (xor = invert the specified Bit in the Register), wait 2 sec, toggle blue, repeat
// 	 _delay_ms(2000);
//  	 PORTB ^= (1<<PB4);
 //=========================================================================================================toggler
// 	_delay_ms(500);
// 		PORTB |= (1<<PB3);		 // Bit 3 set to 1 (red on)
// 		_delay_ms(250);
// 		PORTB &= ~(1<<PB3);		//bit 3 set to 0 (red off)
// 		_delay_ms(250);
// 		PORTB |= (1<<PB4);		//bit 4 set to 1 (blue on)
// 		_delay_ms(250);
// 		PORTB |= (1<<PB3);			// red on
// 		_delay_ms(250);
// 		PORTB &= ~(1<<PB4);			//blue off
// 	 	_delay_ms(250);
//  		
//		}
	
	
// Toggling the FAN_ACC_Switch _PB2 with PWM and overflow flags (8 Bit register)
// normal  Mode
/*===================================================================================================================
int main void is above
 #include <avr/io.h>
 #include <util/delay.h>
 #define F_CPU 1000000UL //1mhz
 int main(void)
 {
 	uint8_t  cycles = 0;
 	DDRB = 0xff;
 	TCNT0 = 0x00;
 	TCCR0A |= (1<<CS10) | (1<<CS12); //set WGM0:1 = 0 for the normal mode, page 110 (8 bit timer) pre scalar 1024
 	
 	
 	//OCR1A = 0xff;
 	while(1)
 	{
 		PORTB ^= (1<<PB3) ; //toggle red (xor = invert the specified Bit in the Register), wait 2 sec, toggle blue, repeat
 		 _delay_ms(2000);
 		PORTB ^= (1<<PB4);
 		while ((TIFR0 & 0x01) == 0x01)  //0x01 = 0b01 means that when TIFRO register is 0b10 'while' works. OCF0A is the 1st bit, TOV0 is the 0th bit
 	{
 			TCNT0 = 0x00;
			TIFR0 = 0x01; //0b0000001;
 			//TIFR0 |=  (1<<TOV0);// | (1<<OCF0A); // clear overflow flag(TOF0) TIFR0 is now 0b11?
 			cycles++;
 			//return (cycles);
 				if (cycles >= 10) //didnt calculate yet, should be enough to observe a toggle on the ACC switch	
 		{
 					//_delay_ms(2000);
 					PORTB ^= (1<<PB3) ;
 					//_delay_ms(600);
 					PORTB ^= (1<<PB4);
 					cycles = 0; //set overflow cycles back to 0	
 			}else{
 			PORTB ^= (1<<PB4);
 		}
 	}
 		PORTB ^= (1<<PB3) ; //toggle red (xor = invert the specified Bit in the Register), wait 2 sec, toggle blue, repeat
 		 _delay_ms(2000); cant make both toggle, cpu is stuck in the previous 'while' repeating cycles
 	}
 		//DOES WORK
 	}
 	===================================================================================================================*/
// 	#include <avr/io.h>
// 	#include "adc_functions.h"
// 	uint16_t value;
// 	int i;
// 	int main(void)
// 	{
// 					//result that will be saved in ADCL / ADCH
// 	
// 	ADMUX |= (1<<REFS0);		// AVCC with external capacitor on AREF pin (page 287)
// 	//ADMUX &= ~(1<<MUX4) ;  // PF0_(ADC0) as input , 1<<MUX0 for PF1_(ADC1)
// 	//ADMUX |= (1<<ADLAR)  // left to right reading,  is this line necessary? havent seen anyone use it in code examples
// 	
// 	
// 	ADCSRA |= (1<<ADEN) | (1<<ADPS2); // Enabling the ADC with a logic one set on ADEN, prescaler 
// 	ADCSRA |= (1<<ADSC); //start the conversion
// 	/*
// 	if (ADCSRA & (1<<ADIF))
// 	{
// 		value = ADC;
// 		ADCSRA |= (1<<ADIF) | (1<<ADSC);
// 	}
// 	*/
// 	while (ADCSRA & (1<<ADSC)) // so long as adsc bit is 1 conversion will run
// 	{
// 		value = ADC; //first reading accuracy is not guaranteed, is recommended to be dismissed
// 		/*value = 0; //dismiss the first reading
// 		for (i=0; i<2; i++)  //3 measurements
// 		{
// 			ADCSRA |= (1<<ADSC); // start converting
// 				while (ADCSRA & (1<<ADSC))
// 				{
// 				value =ADC;
// 				ADCSRA |= (1<<ADIF);
// 				}
// 			value += ADC; //adding all 3 values on top of each other
// 		}
// 		
// 		value /= 2; // average = one reading
// 		*/
// 		ADCSRA |= (1<<ADSC)|(1<<ADIF); //disable ADC with a logic 0 to ADEN
// 		
// 		
// 		
// 	}
// 	
// 	return value;
// 	}   //broken code, needs a do-over
	
		//ADC 2 wie Ole
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "adc_functions.h"
uint16_t adc_value;
int main(void)
{	
DDRB = 0xff;
PORTB |= (1<<PB3);
DDRF = 0;	
ADMUX |= (1<<REFS0);	//AVCC WITH EXTERNAL CAPACITOR ON AREF	
ADMUX &= ~(1<<MUX4) ; // ADC0 AS INPUT
//ADMUX |= (1<<MUX0); //ADC1 as input
ADCSRA |= (1<<ADEN) | (1<<ADPS2); //ENABLE ADC, PRESCALE FREQ
ADCSRA |= (1<<ADSC); // START CONV

	while (ADCSRA & (1<<ADIF))
	{
		adc_value = ADC;
		ADCSRA |= (1<<ADIF) | (1<<ADSC);
		//return adc_value;
	}
	
}


