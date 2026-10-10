#include "voltage_sense.h"
#include "adc.h"

static uint16_t board_voltage_mV = 0U;
static uint16_t bat_sense_mV = 0U;

static uint16_t board_voltage_history[5] = {0};
static uint8_t board_voltage_index = 0U;

/* Erste Messungen wie im ursprünglichen 10er-Zeitblock. */
void VOLTAGE_SENSE_Read(void)
{
    board_voltage_raw = ADC_Read(ADC_CHANNEL_2);
    bat_sense_raw = ADC_Read(ADC_CHANNEL_1);
}

/* Zweite Board-Messung und ursprüngliche Berechnung. */
void VOLTAGE_SENSE_Update(void)
{
    board_voltage_raw = ADC_Read(ADC_CHANNEL_2);

    board_voltage_history[board_voltage_index] = board_voltage_raw;
    board_voltage_index = (board_voltage_index + 1U) % 5U;

    uint32_t sum = 0U;

    for (uint8_t i = 0U; i < 5U; i++)
    {
        sum += board_voltage_history[i];
    }

    uint16_t average = (uint16_t)(sum / 5U);

    float voltage = 20.0f + (average - 2150) * 0.011907f;
    board_voltage_mV = (uint16_t)(voltage * 10.0f);

    bat_sense_mV = (uint16_t)((bat_sense_raw * 3300UL) / 4095UL);
}

uint16_t VOLTAGE_SENSE_GetBoardVoltage(void)
{
    return board_voltage_mV;
}

uint16_t VOLTAGE_SENSE_GetBatSense(void)
{
    return bat_sense_mV;
}
