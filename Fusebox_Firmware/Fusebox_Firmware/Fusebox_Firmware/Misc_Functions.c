#include "Misc_Functions.h"

volatile unsigned long sys_time = 0;



void port_config(){  //0 input, 1 output
	DDRA = 0;
	// WP, fan and LED outputs
	DDRB = 0 | (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB4) | (1<<PB6);
	// Fuse Read Out MUX CTRL
	DDRC = 0 | (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);
	// Activation for R2D and can outputs, PD5 transmits to CAN, PD6 is a receiver
	DDRD = 0 | (1<<PD4);
	// Shutdown Circuit Indicator Inputs, Servo PWM
	DDRE = 0 | (1<<PE4);
	// JTAG and 2 ADC readings inputs
	DDRF = 0;
	// Fuse Read Out Status
	DDRG = 0;
}

void sys_timer_config(void)
{
	//CTC-Mode, /64
	TCCR0A = 0 | (1<<WGM01) | (1<<CS01) | (1<<CS00);
	//Compare value for 1ms (Formula in Datasheet)
	OCR0A = 249; //249
	//Compare Interrupt Enable
	TIMSK0 = 0 | (1<<OCIE0A);
}

void sys_tick_heart()
{
	PORTB ^= (1<<PB2); //toggle the Heart led on Pin 4, will be used in the super loop in main.c to indicade that the loop is running correctly	
};

void fault_not_detected()
{
	PORTB &= ~(1<<PB1); //turn off red led in case of no fault
}

void fault_detected()
{
	PORTB |= (1<<PB1); //turn on red led when called (fault present)
}

int16_t calculate_ac_current(uint16_t limit, uint16_t value){
	
	return (int16_t)((float)limit * ((float)value/10));
}
uint16_t test_ac(uint8_t value){
	
	return (300)*((101-(value))/100);
}
//void controlMotorsBasedOnSteering(uint16_t limit, uint16_t value, int8_t sa) {
	//typedef struct {
		//uint16_t left;
		//uint16_t right;
	//} Motor;
	//
	//Motor current = {0};  // Initialize the struct with 0 values
//
	//// Bound the steering angle between -90 and 90
	//if (sa < -90) sa = -90;
	//if (sa > 90) sa = 90;
	//
	//// Calculate the throttle limit
	//int throttle_limit = (value * limit) / 99;
//
	//if (sa < 0) {
		//// Left turn
		//current.left = limit + (sa * limit / 90);
		//current.right = limit - (sa * limit / 90);
		//} else if (sa > 0) {
		//// Right turn
		//current.left = limit - (sa * limit / 90);
		//current.right = limit + (sa * limit / 90);
		//} else {
		//// Straight
		//current.left = throttle_limit;
		//current.right = throttle_limit;
	//}
//}

ISR(TIMER0_COMP_vect)
{
	sys_time++;	//system time incremented on each interrupt flag from the CTC mode compare register => every OCR0A
}