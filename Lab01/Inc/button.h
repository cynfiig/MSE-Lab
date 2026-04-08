/**
 * @file    button.h
 * @brief   Button module – abstracts B1 (PC13) on the NUCLEO-F446RE.
 * @author  Carlos Cayetano
 * @date    2026-04-07
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "gpio_driver.h"

#define BUTTON_PORT  GPIOC
#define BUTTON_PIN   13U

typedef enum {
    BUTTON_RELEASED = 0U,
    BUTTON_PRESSED  = 1U
} ButtonState_t;

void          button_init(void);
ButtonState_t button_get_state(void);

#endif /* BUTTON_H */
