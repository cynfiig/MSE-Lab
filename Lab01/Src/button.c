/**
 * @file    button.c
 * @brief   Button module implementation – B1 (PC13) on NUCLEO-F446RE.
 * @author  Carlos Cayetano
 * @date    2026-04-07
 */

#include "button.h"

void button_init(void)
{
    GPIO_Config_t cfg = {
        .port  = BUTTON_PORT,
        .pin   = BUTTON_PIN,
        .mode  = GPIO_MODE_INPUT,
        .otype = GPIO_OTYPE_PP,
        .speed = GPIO_SPEED_LOW,
        .pupd  = GPIO_PUPD_PULLUP   /* B1 es activo-LOW */
    };
    GPIO_Init(&cfg);
}

ButtonState_t button_get_state(void)
{
    GPIO_PinState_t raw = GPIO_PIN_RESET;
    GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN, &raw);
    /* IDR=0 → botón presionado (activo-LOW) */
    return (raw == GPIO_PIN_RESET) ? BUTTON_PRESSED : BUTTON_RELEASED;
}
