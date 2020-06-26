#pragma once

#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>

#include <stdint.h>

void timer_setup(enum rcc_periph_clken rcc_clken, uint32_t timer_peripheral, uint32_t prescaler, uint32_t period);

void timer_setup_output_c(uint32_t timer_peripheral, enum tim_oc_id oc_id, enum tim_oc_mode oc_mode, uint32_t oc_value);

void timer_start(uint32_t timer_peripheral);
