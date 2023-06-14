/*
 * fan_power_unit_control.c
 *
 * Created: 10.04.2023 15:52:18
 *  Author: adaam
 */ 

/*
 ***********************************************************************************************************************************************************************************************
 *															  SETUP AND CALCULATION OF THE FAN POWER UNIT PWM SIGNAL
 *
 * Description : This c file contains 2 functions and an interrupt service routine. "timer1_config()" sets up the 16-bit Timer/Counter1, responsible for controlling 
 *				 the output frequency and initialization of said Timer/Counter on Pin OC1B (PB6). As described on page 113 of the data sheet, we are handling a
 *				 16-bit timer here, which allows for a wider range of frequencies than an 8-bit one. For a quick overview of available modes of operation refer to
 *				 page 138 of the data sheet. For the purpose of controlling a fan power unit we have decided to utilize a Fast PWM signal with the TOP value stored in 
 *				 the OCR1A register and the BOTTOM value stored in the OCR1B register. A Fast PWM signal gives us the widest range of frequencies to choose from and "Mode 15"
 *				 was selected for its flexibility when it comes to modulating the duty cycle.
 *				 
 **				 The "fan_power_unit_PWM_control" function executes a simple arithmetic calculation based on the variable "temperature" referring to the temperature of the 
 *				 physical engine on our TY22evo vehicle. The temperature is communicated to the Fusebox utilizing the CAN Bus Protocol and is contained in the Data byte [x] of 
 *				 a MOb with the following id [placeholder]. Once the threshold temperature is reached, an if-statement will execute the line of code responsible for calculating 
 *				 the duty cycle variable, which will subsequently update the BOTTOM value (OCR1B) of our timer.
 *
 **				"ISR(TIMER1_COMPA_vect)" is an Interrupt Service Routine that executes the code contained within itself whenever the Timer value (TCNT1) matches our predefined TOP stored
 *				in the OCR1A register. In this case the generated Output Compare Interrupt is utilized to update the BOTTOM value (OCR1B) and either widen or narrow the duty cycle.
 *
 * Notes       : 1) Something that i was not used to is the need to  utilize 2 Control registers of the Timer1. To access its extended list of operation modes, the user needs to
 *                  make use of both TCCR1A and TCCR1B so that the full initialization is complete. Always make yourself familiar with "X-bit Timer/Counter Register Description"
 *					section of the documentation to avoid any confusion that may lead to writing values to wrong registers. For example the Clock Select Bit CS11 is located
 *					in the B register of our timer but out of habit I set the bits of the register TCCR1A first and like any other timer i chose my frequency Clock Select value straight away
 *					unaware of the fact that the TCR1A register does not contain it. Only after a few hours i realized where the Clock Select bits are supposed to be set (in the TCR1B register).
 *				 2) As of now the Fan timer is always running with the base duty cycle of close to 1% before TEMP_MIN is reached, the code does not include an functionality of the fan powering 
 *					on and off yet. Additionally no case for temperature < TEMP_MIN is defined. This will lead to fan always running on its lowest duty cycle as long as TEMP_MIN stays below the
 *					threshold level. (weiss noch nicht ob der fan ein case fuer aussalten haben soll)
 ***********************************************************************************************************************************************************************************************
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "fan_power_unit_PWM_control.h"

volatile uint8_t fan_duty = 0;		
extern volatile uint8_t temperature;
void fan_power_unit_PWM_control(uint8_t temperature, uint8_t fan_duty){	  //FIX THIS FUNCTION LATER, RN CALCULATION WITHIN THE SUPER LOOP
	if (temperature > TEMP_MAX){		// defining a maximum for the temperature, duty cycle 100% past that maximum
		temperature = TEMP_MAX;
	}
	if (temperature >= TEMP_MIN){		// calculating the duty cycle
		fan_duty = (temperature*63)/100;
	}	
}

void timer1_config(){	
DDRB |= (1<<PB6);			// setting COM1nx Bits not necessary because we can also toggle/set pins using the ISR, here the Fan PWM cable is already on the Pin toggled by those bits											
TCCR1A = (1<<WGM11) | (1<<WGM10) | (0<<COM1A1) | (1<<COM1A0) | (1<<COM1B1);	//mode 15, prescaler 8, non inverted mode => page 138 - 139  
TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11);								// Fast PWM description => page 128
TIMSK1 = (1<<OCIE1A);														//Output Compare interrupt flag will be set whenever OCR1A is reached
OCR1A = 63;													// TOP  16000000/(8*(1+64)) = 30769.23077 Hz = ~30kHz => page 130   with TOP value 62+1 the resolution is 6 bit => page 128
OCR1B = 0;													// BOTTOM
}

ISR(TIMER1_COMPA_vect){									//ISR for the timer 1, updating the duty cycle
//cli();
OCR1B = fan_duty;
//sei();
}