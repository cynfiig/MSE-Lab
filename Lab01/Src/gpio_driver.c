/**
 * @file    gpio_driver.c
 * @brief   GPIO Driver implementation – STM32F446RE register-level access.
 * @author  Carlos Cayetano
 * @date    2026-04-07
 */

#include "gpio_driver.h"

static GPIO_Status_t validate(GPIO_RegDef_t *port, uint8_t pin)
{
    if (port == NULL) return GPIO_ERR_NULL_PORT;
    if (pin > 15U)   return GPIO_ERR_INVALID_PIN;
    return GPIO_OK;
}

GPIO_Status_t GPIO_EnableClock(GPIO_RegDef_t *port)
{
    if (port == NULL) return GPIO_ERR_NULL_PORT;

    if      (port == GPIOA) { RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN; }
    else if (port == GPIOB) { RCC_AHB1ENR |= RCC_AHB1ENR_GPIOBEN; }
    else if (port == GPIOC) { RCC_AHB1ENR |= RCC_AHB1ENR_GPIOCEN; }
    else if (port == GPIOD) { RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN; }
    else if (port == GPIOE) { RCC_AHB1ENR |= RCC_AHB1ENR_GPIOEEN; }
    else if (port == GPIOF) { RCC_AHB1ENR |= RCC_AHB1ENR_GPIOFEN; }
    else if (port == GPIOG) { RCC_AHB1ENR |= RCC_AHB1ENR_GPIOGEN; }
    else if (port == GPIOH) { RCC_AHB1ENR |= RCC_AHB1ENR_GPIOHEN; }
    else return GPIO_ERR_NULL_PORT;

    return GPIO_OK;
}

GPIO_Status_t GPIO_Init(const GPIO_Config_t *config)
{
    if (config == NULL) return GPIO_ERR_NULL_PORT;

    GPIO_Status_t status = validate(config->port, config->pin);
    if (status != GPIO_OK) return status;

    status = GPIO_EnableClock(config->port);
    if (status != GPIO_OK) return status;

    uint8_t pin = config->pin;

    /* MODER – 2 bits per pin */
    config->port->MODER &= ~(0x3UL << (pin * 2U));
    config->port->MODER |=  ((uint32_t)config->mode << (pin * 2U));

    /* OTYPER – 1 bit per pin */
    config->port->OTYPER &= ~(0x1UL << pin);
    config->port->OTYPER |=  ((uint32_t)config->otype << pin);

    /* OSPEEDR – 2 bits per pin */
    config->port->OSPEEDR &= ~(0x3UL << (pin * 2U));
    config->port->OSPEEDR |=  ((uint32_t)config->speed << (pin * 2U));

    /* PUPDR – 2 bits per pin */
    config->port->PUPDR &= ~(0x3UL << (pin * 2U));
    config->port->PUPDR |=  ((uint32_t)config->pupd << (pin * 2U));

    return GPIO_OK;
}

GPIO_Status_t GPIO_WritePin(GPIO_RegDef_t *port, uint8_t pin, GPIO_PinState_t state)
{
    GPIO_Status_t status = validate(port, pin);
    if (status != GPIO_OK) return status;

    /* BSRR: bits[15:0] set, bits[31:16] reset – atomic, no RMW needed */
    if (state == GPIO_PIN_SET)
        port->BSRR = (1UL << pin);
    else
        port->BSRR = (1UL << (pin + 16U));

    return GPIO_OK;
}

GPIO_Status_t GPIO_ReadPin(GPIO_RegDef_t *port, uint8_t pin, GPIO_PinState_t *state)
{
    GPIO_Status_t status = validate(port, pin);
    if (status != GPIO_OK) return status;
    if (state == NULL)     return GPIO_ERR_NULL_PORT;

    *state = (GPIO_PinState_t)((port->IDR >> pin) & 0x1UL);
    return GPIO_OK;
}

GPIO_Status_t GPIO_TogglePin(GPIO_RegDef_t *port, uint8_t pin)
{
    GPIO_Status_t status = validate(port, pin);
    if (status != GPIO_OK) return status;

    port->ODR ^= (1UL << pin);
    return GPIO_OK;
}
