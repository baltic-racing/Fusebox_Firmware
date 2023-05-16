/*
 * shutdown_circuit_indicator.c
 *
 * Created: 10.04.2023 15:34:19
 *  Author: adaam
 */ 
 #include <avr/io.h>
 #include <avr/interrupt.h>
uint8_t SCI_read_out(){
	
	return PINC;
}
