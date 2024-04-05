#ifndef SHUTDOWN_CIRCUIT_INDICATOR_H_
#define SHUTDOWN_CIRCUIT_INDICATOR_H_

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t SDCI_read_out(char mux_select);

#endif /* SHUTDOWN_CIRCUIT_INDICATOR_H_ */