#include "Fuse_Read_Out.h"

uint8_t Fuse_Read_Out(char mux_select)
{
	PORTC = mux_select;
	return PING1;
}