/*
 * cooling_control.c
 *
 *  Created on: 07.10.2026
 *      Author: Lilly
 */

#include "cooling_control.h"
#include "main.h"
#include "tim.h"
#include "fdcan.h"

#define WP_start_time        5000U
#define TSAC_FANS_start_time 10000U
#define Radiator_start_time  15000U
#define TSAC_PWM_PERIOD_TICKS 2150U
#define TSAC_PWM_HIGH_TICKS   1247U  /* 58 % von 2150 */
#define TSAC_PWM_LOW_TICKS     903U

static volatile uint32_t tsac_pwm_pulse_count = 0U;
static volatile uint8_t tsac_pwm_enabled = 0U;
static uint8_t tsac_pwm_high_phase = 0U;
static uint8_t radiator_startup_complete = 0U;
static uint8_t fanspeed = 12U;

void WP_HSD_Init(void)
{
    HAL_GPIO_WritePin(WP_SW_GPIO_Port, WP_SW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Reset_WP_GPIO_Port, Reset_WP_Pin, GPIO_PIN_SET);
}

void FAN_RADIATOR_HSD_Init(void)
{
    HAL_GPIO_WritePin(FAN_Radiator_SW_GPIO_Port,
                      FAN_Radiator_SW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Reset_Radiator_GPIO_Port,
                      Reset_Radiator_Pin, GPIO_PIN_SET);
}

void TSAC_FANS_Init(void)
{
    HAL_GPIO_WritePin(FAN_TSAC_SW_GPIO_Port,
                      FAN_TSAC_SW_Pin, GPIO_PIN_SET);

    tsac_pwm_enabled = 1U;
}

void setFanSpeed(uint8_t percent)
{
    uint32_t ccr = (percent * 1000U) / 100U;
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, ccr);
}

void COOLING_CONTROL_Update(void)
{
    if (radiator_startup_complete)
    {
        uint8_t inv_temp_r_C;

        if (inv_temp_r_raw < 100 || inv_temp_r_raw > 640)
        {
            inv_temp_r_C = 65U;
        }
        else
        {
            inv_temp_r_C = (uint8_t)(inv_temp_r_raw / 10);
        }

        fanspeed = inv_temp_r_C + 35U;
        setFanSpeed(fanspeed);
    }
}

void COOLING_CONTROL_Startup(uint32_t now)
{
    if (radiator_startup_complete == 0U)
    {
        if (now > WP_start_time)
        {
            WP_HSD_Init();
        }

        if (now > TSAC_FANS_start_time)
        {
            TSAC_FANS_Init();
        }

        if (now > Radiator_start_time)
        {
            FAN_RADIATOR_HSD_Init();

            fanspeed += 1U;
            setFanSpeed(fanspeed);

            if (fanspeed > 34U)
            {
                radiator_startup_complete = 1U;
            }
        }
    }
}
void TSAC_PWM_Init(void)
{
    tsac_pwm_enabled = 0U;
    tsac_pwm_high_phase = 0U;
    tsac_pwm_pulse_count = 0U;

    HAL_GPIO_WritePin(FAN_TSAC_CTRL_GPIO_Port,
                      FAN_TSAC_CTRL_Pin, GPIO_PIN_RESET);

    __HAL_TIM_SET_COUNTER(&htim6, 0U);
    __HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);

    if (HAL_TIM_Base_Start_IT(&htim6) != HAL_OK)
    {
        Error_Handler();
    }
}

void TSAC_PWM_TimerElapsed(TIM_HandleTypeDef *htim)
{
    if (htim->Instance != TIM6)
    {
        return;
    }

    if (tsac_pwm_enabled == 0U)
    {
        tsac_pwm_high_phase = 0U;

        HAL_GPIO_WritePin(FAN_TSAC_CTRL_GPIO_Port,
                          FAN_TSAC_CTRL_Pin, GPIO_PIN_RESET);

        __HAL_TIM_SET_AUTORELOAD(htim,
                                TSAC_PWM_PERIOD_TICKS - 1U);
        return;
    }

    if (tsac_pwm_high_phase == 0U)
    {
        tsac_pwm_high_phase = 1U;
        tsac_pwm_pulse_count++;

        HAL_GPIO_WritePin(FAN_TSAC_CTRL_GPIO_Port,
                          FAN_TSAC_CTRL_Pin, GPIO_PIN_SET);

        __HAL_TIM_SET_AUTORELOAD(htim,
                                TSAC_PWM_HIGH_TICKS - 1U);
    }
    else
    {
        tsac_pwm_high_phase = 0U;

        HAL_GPIO_WritePin(FAN_TSAC_CTRL_GPIO_Port,
                          FAN_TSAC_CTRL_Pin, GPIO_PIN_RESET);

        __HAL_TIM_SET_AUTORELOAD(htim,
                                TSAC_PWM_LOW_TICKS - 1U);
    }
}
uint8_t TSAC_PWM_IsEnabled(void)
{
    return tsac_pwm_enabled;
}

uint8_t TSAC_PWM_GetDuty(void)
{
    return 58U;
}

uint32_t TSAC_PWM_GetPulseCount(void)
{
    return tsac_pwm_pulse_count;
}
