#include <avr/io.h>
#include <avr/interrupt.h>
uint16_t fuse_read_out(){
	return PINE | PINA << 8;
}