 #include <avr/io.h>
 #include <avr/interrupt.h>
 
uint8_t SDCI_read_out(char mux_select)
{
	PORTC = mux_select;	
	return PING1;
}
