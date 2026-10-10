#include "current_sense.h"
#include "adc.h"

void CURRENT_SENSE_Update(void)
{
    currentsense_radiator_raw = ADC_Read(ADC_CHANNEL_3);
    currentsense_wp_raw = ADC_Read(ADC_CHANNEL_4);
    currentsense_mab_raw = ADC_Read(ADC_CHANNEL_6);
    currentsense_gp_raw = ADC_Read(ADC_CHANNEL_7);
}
