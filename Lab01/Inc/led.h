/**
 * @file    led.h
 * @brief   LED module – abstracts LD2 (PA5) on the NUCLEO-F446RE.
 * @author  Carlos Cayetano
 * @date    2026-04-07
 */

#ifndef LED_H
#define LED_H

#include "gpio_driver.h"

#define LED_PORT   GPIOA
#define LED_PIN    5U

void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif /* LED_H */
