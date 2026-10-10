/*
 * CAN_DATA.c
 *
 *  Created on: 07.10.2026
 *      Author: Lilly
 */

#include "CAN_DATA.h"
#include "FRO.h"
#include "fdcan.h"
#include "cooling_control.h"
#include "adc.h"

void CAN_DATA_Init(void)
{
    config_FDCAN1();
}

void CAN_DATA_SendFusebox0(uint16_t bat_sense_mV,
                          uint16_t board_voltage_mV,
                          uint16_t sdc_status)
{
    uint16_t fro_status = FRO_GetStatus();

    TxData1[0] = (uint8_t)bat_sense_mV;
    TxData1[1] = (uint8_t)(bat_sense_mV >> 8);
    TxData1[2] = (uint8_t)board_voltage_mV;
    TxData1[3] = (uint8_t)(board_voltage_mV >> 8);
    TxData1[4] = (uint8_t)sdc_status;
    TxData1[5] = (uint8_t)(sdc_status >> 8);

    TxData1[6] = (uint8_t)(fro_status & 0xFFU);
    TxData1[7] = (uint8_t)((fro_status >> 8) & 0x3FU);

    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,
                                    &TxHeader1,
                                    TxData1) != HAL_OK)
    {

    }
}
void CAN_DATA_SendTsacPWM(void)
{
    static uint32_t previous_pulse_count = 0U;

    uint32_t pulse_count = TSAC_PWM_GetPulseCount();

    uint16_t pulses =
        (uint16_t)(pulse_count - previous_pulse_count);

    previous_pulse_count = pulse_count;

    /* Header kopieren und die zusätzliche CAN-ID einstellen. */
    FDCAN_TxHeaderTypeDef header = TxHeader1;
    header.Identifier = 0x602U;

    uint8_t data[8] = {0};

    data[0] = TSAC_PWM_IsEnabled();
    data[1] = TSAC_PWM_GetDuty();

    /* Pulsanzahl: niederwertiges Byte zuerst. */
    data[2] = (uint8_t)(pulses & 0xFFU);
    data[3] = (uint8_t)(pulses >> 8);

    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,
                                    &header,
                                    data) != HAL_OK)
    {
        /* Bei Sendefehlern weiterlaufen, wie bei 0x600. */
    }
}
void CAN_DATA_SendCurrentSense(void)
{
    /* Bestehenden Header kopieren; 0x600 bleibt unverändert. */
    FDCAN_TxHeaderTypeDef header = TxHeader1;
    header.Identifier = 0x610U;

    uint8_t data[8];

    /* MAB: Byte 0 und 1. */
    data[0] = (uint8_t)(currentsense_mab_raw & 0xFFU);
    data[1] = (uint8_t)(currentsense_mab_raw >> 8);

    /* GP: Byte 2 und 3. */
    data[2] = (uint8_t)(currentsense_gp_raw & 0xFFU);
    data[3] = (uint8_t)(currentsense_gp_raw >> 8);

    /* Radiator: Byte 4 und 5. */
    data[4] = (uint8_t)(currentsense_radiator_raw & 0xFFU);
    data[5] = (uint8_t)(currentsense_radiator_raw >> 8);

    /* Wasserpumpe: Byte 6 und 7. */
    data[6] = (uint8_t)(currentsense_wp_raw & 0xFFU);
    data[7] = (uint8_t)(currentsense_wp_raw >> 8);

    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,
                                    &header,
                                    data) != HAL_OK)
    {
        /* Wie bei den bestehenden Nachrichten weiterlaufen. */
    }
}
