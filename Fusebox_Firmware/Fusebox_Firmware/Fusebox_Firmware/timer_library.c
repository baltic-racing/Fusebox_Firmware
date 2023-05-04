/*
 * timer_library.c
 *
 * Created: 04.05.2023 08:10:28
 *  Author: adaam
 */ 
#include "timer_library.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define CLK_IO 16000000  //put your base clk_io timer in here (for example the 16 MHz at90can128 timer)

int timer_frequency = 0;

int frequencies[5000];

//f[1] = freq with pre of 1
//f[2] = freq with pre of 8
//f[3] = freq with pre of 64
// ...
//uint16_t prescaler[5];

	
void timer0_config(int freq, uint8_t mode,uint16_t prescaler[5], uint8_t Compare_Output_Mode){
	prescaler[0] = 0;  //can  make this array shorter, by removing the 0 => in the for loop use an expression "TCCR0A |= j+1" (eliminates the pointless 0+1 =1 => 1+1 =2 etc ...
	prescaler[1] = 1;	//prescaler [0] = 1;
	prescaler[2] = 8;
	prescaler[3] = 64;
	prescaler[4] = 256;
	prescaler[5] = 1024;
	switch (mode)
	{
	case Normal_Mode:  
			TCCR0A &= ~(1<<WGM00) | ~(1<WGM01);
			
			
		
	break;
	case CTC_Mode:
			switch(Compare_Output_Mode){
				case 1:	TCCR0A |= (1<<COM0A0);  //toggling port
				break;
				case 2: TCCR0A |= (1<<COM0A1);	//port low on compare (non inverted mode?)
				break;
				case 3:	TCCR0A |= (1<<COM0A1) | (1<<COM0A0); //port high on compare (inverted mode?)
				break;
			}
			uint8_t TOP[256];  
			//need to go through way more frequency possibilities to accommodate the wide range of the OCR0A register (8 bit = 2^8 = 256 frequencies for EACH prescaler = 1280 combinations)
			TCCR0A |= (1<<WGM01);
			for (uint8_t k = 0; k < 6; k++){  // both k and j progressing at the same rate? each k needs to wait for 256 frequency calculations before moving to the subsequent prescaler
				for (uint16_t j = 0; j < 256; j++){   //why not just j = 1, at 0 nothing happens => wasted time 
					frequencies[j] = CLK_IO/(2*prescaler[k]*(1+TOP[j])); //holy moly  this gonna be slow => solution is using cache?
					if (frequencies[j] == freq){
						TCCR0A |= k;
						OCR0A = j; 
					}
				}
			}
	break;
	case Fast_PWM_Mode:   // ADD COM0A1 INVERTED NON INVERTED OPTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			TCCR0A |= (1<<WGM01) | (1<<WGM00);
			for (uint8_t j = 0; j < 6; j++ ){  //will it only run once?  use a while(presacler < 6) otherwise to limit it
				frequencies[j] = CLK_IO/(prescaler[j]*256); //fill my array with all 5 possible frequencies
				for (uint8_t i = 0; i <= 5; i++){		//this is most likely a redundant loop, delete later
																//need to go through them (bot to top) and pick a frequency out that matches the desired value (user can only choose between the 5)
					if (frequencies[j] == freq){							//	terrible optimization, imagine that the matching frequency is 10 GHz, it may take a while before
						TCCR0A |= j;  //j between 0 and 5						this function reaches that value => solution is a pointer?
					}
				}
			}		
	break;
	case Phase_Correct_PWM_Mode: 
			TCCR0A |= (1<<WGM00); //same as fast PWM but twice as slow + different WGMxn register setting
	break;	
	}
}
