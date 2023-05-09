/*
 * timer_library.h
 *
 * Created: 04.05.2023 08:11:35
 *  Author: adaam
 */ 



#ifndef TIMER_LIBRARY_H_
#define TIMER_LIBRARY_H_
// modes
#define Normal_Mode 1
#define CTC_Mode 2
#define Fast_PWM_Mode 3
#define Phase_Correct_PWM_Mode 4
//compare output modes
#define Toggle_Port 1
#define Non_Inverted_Mode 2
#define Inverted_Mode 3
#define No_Mode 4

//void timer0_config(int freq, uint8_t mode,uint16_t prescaler[5], uint8_t Compare_Output_Mode);

#endif /* TIMER_LIBRARY_H_ */