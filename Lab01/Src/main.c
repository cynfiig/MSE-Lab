/**
 * @file    main.c
 * @brief   Aplicación – Toggle LD2 cada vez que se presiona B1 (NUCLEO-F446RE).
 * @author  Carlos Cayetano
 * @date    2026-04-07
 */

#include "led.h"
#include "button.h"

#define DEBOUNCE_CYCLES  5000U

static void delay_cycles(volatile uint32_t cycles)
{
    while (cycles--) { __asm volatile ("nop"); }
}

static int debounced_press(void)
{
    for (uint32_t i = 0U; i < DEBOUNCE_CYCLES; i++) {
        if (button_get_state() != BUTTON_PRESSED) return 0;
    }
    return 1;
}

int main(void)
{
    led_init();
    button_init();

    while (1) {
        if (debounced_press()) {
            led_toggle();
            /* Esperar a que suelten el botón */
            while (button_get_state() == BUTTON_PRESSED) {
                delay_cycles(100U);
            }
            delay_cycles(DEBOUNCE_CYCLES);
        }
    }
    return 0;
}
