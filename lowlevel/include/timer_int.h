/**
 * @file
 * 
 * This file is part of cdfr2020CarteCerveauProg
 * 
 * @brief This implements a routine for periodic call of a function
 * 
 * reference used code by Ken Sarkies ksarkies@trinity.asn.au
 * https://github.com/ksarkies/ARM-Ports/blob/master/test-libopencm3-stm32f1/timer-interrupt-oc-et-stm32f103.c
 * 
 * @date  12/2020  
 * 
 * Licence :
 * 
 * Robotronik Phelma
 * @author NPXav Benano
*/


#pragma once

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

#include "timer.h"
#include "gpio.h"
#include "uart.h"

/**
 * Prescale 64000000 Hz system clock by 64 = 1000000 Hz.
 */
#define INT_TIM_PRESCALER	(32000)

/**
 * Period for the Timer [ms]
 */
#define INT_TIM_PERIOD		(1000)

/**
 * @defgroup INT_TIM int_tim
 * @{
 * @brief Internal timer that will generate interrupts to get tof sensor measurement TIM4
 * 
 */
#define INT_TIM_RCC				RCC_TIM3
#define INT_TIM					TIM3
#define INT_TIM_NVIC            NVIC_TIM3_IRQ
#define INT_TIM_DIER_UIE        TIM_DIER_UIE
#define INT_TIM_SR_UIF          TIM_SR_UIF
/** @} */

void timer_setup_interrupt();
void tim3_isr();