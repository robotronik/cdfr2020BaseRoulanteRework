#pragma once

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void gpio_setup_pin_af(uint32_t gpio_port, uint16_t gpio_pin, uint8_t gpio_altfun);