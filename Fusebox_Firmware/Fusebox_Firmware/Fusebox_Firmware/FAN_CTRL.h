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

#define AKKUFAN_DDR		DDRB
#define AKKUFAN_PORT	PORTB
#define AKKUFAN_PIN		PB0

#define FANSPEEDMIN 2300
#define FANSPEEDMAX 3500
#define TEMPMAX 90
#define TEMPMIN 30

// Calculating the Output Compare Match Value for Power Unit f_PWM
// Formula on Page 129 in Datasheet for 30kHz, 16 MHz and Prescaler = 8
// Edit Prescaler in timer1_config if needed

uint16_t getfanspeed(uint8_t temp);
void toggleAkkufan();
void timer1_config();


ISR(TIMER1_COMPA_vect);

#endif /* FAN_CTRL_H_ */