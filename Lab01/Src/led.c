/**
 * @file    led.c
 * @brief   LED module implementation – LD2 (PA5) on NUCLEO-F446RE.
 * @author  Carlos Cayetano
 * @date    2026-04-07
 */

#include "led.h"

void led_init(void)
{
    GPIO_Config_t cfg = {
        .port  = LED_PORT,
        .pin   = LED_PIN,
        .mode  = GPIO_MODE_OUTPUT,
        .otype = GPIO_OTYPE_PP,
        .speed = GPIO_SPEED_LOW,
        .pupd  = GPIO_PUPD_NONE
    };
    GPIO_Init(&cfg);
    led_off();
}

void led_on(void)     { GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);   }
void led_off(void)    { GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); }
void led_toggle(void) { GPIO_TogglePin(LED_PORT, LED_PIN);                }
