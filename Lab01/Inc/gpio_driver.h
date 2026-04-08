/**
 * @file    gpio_driver.h
 * @brief   GPIO Driver – Register-level API for STM32F446RE (NUCLEO-F446RE)
 * @author  Carlos Cayetano
 * @date    2026-04-07
 *
 * Functional Requirements covered: FR-1 … FR-10
 *   FR-1  : Driver shall support ports A–H.
 *   FR-2  : Driver shall support pins 0–15.
 *   FR-3  : Driver shall configure pin mode (Input / Output / AF / Analog).
 *   FR-4  : Driver shall configure output type (Push-Pull / Open-Drain).
 *   FR-5  : Driver shall configure output speed (Low / Medium / High / Very-High).
 *   FR-6  : Driver shall configure pull-up / pull-down / no-pull resistors.
 *   FR-7  : Driver shall write a digital value to an output pin.
 *   FR-8  : Driver shall read a digital value from an input pin.
 *   FR-9  : Driver shall toggle an output pin.
 *   FR-10 : Driver shall return an error code for invalid port or pin arguments.
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

/* ─── Peripheral base addresses ──────────────────────────────────────────── */
#define GPIOA_BASE  0x40020000UL
#define GPIOB_BASE  0x40020400UL
#define GPIOC_BASE  0x40020800UL
#define GPIOD_BASE  0x40020C00UL
#define GPIOE_BASE  0x40021000UL
#define GPIOF_BASE  0x40021400UL
#define GPIOG_BASE  0x40021800UL
#define GPIOH_BASE  0x40021C00UL

#define RCC_BASE    0x40023800UL
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30UL))

#define RCC_AHB1ENR_GPIOAEN  (1UL << 0)
#define RCC_AHB1ENR_GPIOBEN  (1UL << 1)
#define RCC_AHB1ENR_GPIOCEN  (1UL << 2)
#define RCC_AHB1ENR_GPIODEN  (1UL << 3)
#define RCC_AHB1ENR_GPIOEEN  (1UL << 4)
#define RCC_AHB1ENR_GPIOFEN  (1UL << 5)
#define RCC_AHB1ENR_GPIOGEN  (1UL << 6)
#define RCC_AHB1ENR_GPIOHEN  (1UL << 7)

/* ─── GPIO register map ───────────────────────────────────────────────────── */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_RegDef_t;

#define GPIOA  ((GPIO_RegDef_t *)GPIOA_BASE)
#define GPIOB  ((GPIO_RegDef_t *)GPIOB_BASE)
#define GPIOC  ((GPIO_RegDef_t *)GPIOC_BASE)
#define GPIOD  ((GPIO_RegDef_t *)GPIOD_BASE)
#define GPIOE  ((GPIO_RegDef_t *)GPIOE_BASE)
#define GPIOF  ((GPIO_RegDef_t *)GPIOF_BASE)
#define GPIOG  ((GPIO_RegDef_t *)GPIOG_BASE)
#define GPIOH  ((GPIO_RegDef_t *)GPIOH_BASE)

/* ─── Enumerations ────────────────────────────────────────────────────────── */
typedef enum { GPIO_MODE_INPUT=0x00U, GPIO_MODE_OUTPUT=0x01U, GPIO_MODE_AF=0x02U, GPIO_MODE_ANALOG=0x03U } GPIO_Mode_t;
typedef enum { GPIO_OTYPE_PP=0U, GPIO_OTYPE_OD=1U } GPIO_OType_t;
typedef enum { GPIO_SPEED_LOW=0x00U, GPIO_SPEED_MEDIUM=0x01U, GPIO_SPEED_HIGH=0x02U, GPIO_SPEED_VHIGH=0x03U } GPIO_Speed_t;
typedef enum { GPIO_PUPD_NONE=0x00U, GPIO_PUPD_PULLUP=0x01U, GPIO_PUPD_PULLDOWN=0x02U } GPIO_PuPd_t;
typedef enum { GPIO_PIN_RESET=0U, GPIO_PIN_SET=1U } GPIO_PinState_t;
typedef enum { GPIO_OK=0, GPIO_ERR_NULL_PORT=-1, GPIO_ERR_INVALID_PIN=-2 } GPIO_Status_t;

/* ─── Config structure ────────────────────────────────────────────────────── */
typedef struct {
    GPIO_RegDef_t *port;
    uint8_t        pin;
    GPIO_Mode_t    mode;
    GPIO_OType_t   otype;
    GPIO_Speed_t   speed;
    GPIO_PuPd_t    pupd;
} GPIO_Config_t;

/* ─── Public API ─────────────────────────────────────────────────────────── */
GPIO_Status_t GPIO_Init(const GPIO_Config_t *config);
GPIO_Status_t GPIO_WritePin(GPIO_RegDef_t *port, uint8_t pin, GPIO_PinState_t state);
GPIO_Status_t GPIO_ReadPin(GPIO_RegDef_t *port, uint8_t pin, GPIO_PinState_t *state);
GPIO_Status_t GPIO_TogglePin(GPIO_RegDef_t *port, uint8_t pin);
GPIO_Status_t GPIO_EnableClock(GPIO_RegDef_t *port);

#endif /* GPIO_DRIVER_H */
