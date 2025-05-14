 #include "ShutDown_Circuit_Indicator.h"
 

 
uint8_t SDCI_read_out() 
{
	uint8_t SDCI = 0;	
	uint8_t pin_order[] = {3, 5, 0, 7, 2, 1, 6};
	
	uint8_t SDCI_read = (PINE & (0xEF));
	
	for(uint8_t i=0; i< sizeof(pin_order); i++)
	{
		uint8_t pin = pin_order[i];
		
		if ((SDCI_read & (1<<pin) )== 0)
		{
		SDCI  = (1<<pin);
		break;
		}
	
	}
	return SDCI;
	
}
