/*
 * shutdown_circuit_indicator.h
 *
 * Created: 10.04.2023 15:45:36
 *  Author: adaam
 */ 


#ifndef SHUTDOWN_CIRCUIT_INDICATOR_H_
#define SHUTDOWN_CIRCUIT_INDICATOR_H_

#include <avr/io.h>
#include <avr/interrupt.h>
//uint8_t SCI_read_out();

#define SCI_read_out() (uint8_t) PINC

//C pins
#define SCI_TSMS_5V		(uint8_t)	(PINC & 1)
#define SCI_INV0_5V		(uint8_t)	((PINC << 1) & 1)
#define SCI_TSAC_5V		(uint8_t)	((PINC << 2) & 1)
#define SCI_SDB_Left_5V	(uint8_t)	((PINC << 3) & 1)
#define SCI_HV_Distri_5V(uint8_t)	((PINC << 4) & 1)
#define SCI_SDB_Right_5V(uint8_t)	((PINC << 5) & 1)
#define SCI_INV1_5V		(uint8_t)	((PINC << 6) & 1)

#endif /* SHUTDOWN_CIRCUIT_INDICATOR_H_ */