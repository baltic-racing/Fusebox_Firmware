#ifndef FAN_CTRL_H_
#define FAN_CTRL_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define FAN1_DDR		DDRB
#define FAN1_PORT		PORTB
#define FAN1_PIN		PB6

#define FAN2_DDR		DDRE
#define FAN2_PORT		PORTE   
#define FAN2_PIN		PE4  //Servo pin

#define TEMP_MAX 100
#define TEMP_MIN 5

#define DR_MAX 99

// Calculating the Output Compare Match Value for Power Unit f_PWM
// Formula on Page 129 in Datasheet for 30kHz, 16 MHz and Prescaler = 8
// Edit Prescaler in timer1_config if needed

#define f_PWM 30000

uint16_t FAN_PU_SET_PWM(uint16_t temp);
void timer1_config();


ISR(TIMER1_COMPA_vect);

#endif /* FAN_CTRL_H_ */