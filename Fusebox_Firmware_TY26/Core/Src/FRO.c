/*
 * FRO.c
 *
 *  Created on: Oct 4, 2026
 *      Author: Lilly
 */
#include "FRO.h"
#include "main.h"

static uint16_t fro_status = 0U;
static uint8_t fro_channel = 0U;
static uint32_t fro_last_ms = 0U;

/* Die vier Auswahlpins bestimmen den Multiplexerkanal. */
static void FRO_SelectChannel(uint8_t channel)
{
    HAL_GPIO_WritePin(MUX_S0_GPIO_Port, MUX_S0_Pin,
                      (channel & 0x01U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MUX_S1_GPIO_Port, MUX_S1_Pin,
                      (channel & 0x02U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MUX_S2_GPIO_Port, MUX_S2_Pin,
                      (channel & 0x04U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MUX_S3_GPIO_Port, MUX_S3_Pin,
                      (channel & 0x08U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void FRO_Init(uint32_t now_ms)
{
    fro_status = 0U;
    fro_channel = 0U;
    fro_last_ms = now_ms;

    FRO_SelectChannel(fro_channel);
}

void FRO_Task(uint32_t now_ms)
{
    if ((uint32_t)(now_ms - fro_last_ms) < 100U)
    {
        return;
    }

    fro_last_ms = now_ms;

    /* Den ausgewählten Kanal lesen und sein Statusbit aktualisieren. */
    if (HAL_GPIO_ReadPin(FRO_out_GPIO_Port, FRO_out_Pin) == GPIO_PIN_SET)
    {
        fro_status |= (uint16_t)(1U << fro_channel);
    }
    else
    {
        fro_status &= (uint16_t)~(1U << fro_channel);
    }

    /* Nächsten Kanal auswählen; nach Kanal 13 wieder bei 0 beginnen. */
    fro_channel++;
    if (fro_channel >= 14U)
    {
        fro_channel = 0U;
    }

    FRO_SelectChannel(fro_channel);
}

uint16_t FRO_GetStatus(void)
{
    return fro_status;
}
