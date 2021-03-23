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

#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

#include "timer.h"
#include "gpio.h"
#include "uart.h"

/**
 * Prescale 64000000 Hz system clock by 64 = 1000000 Hz.
 */
#define INT_TIM_PRESCALE	(64)

/**
 * Period for the Timer [us]
 */
#define INT_TIM_PERIOD		(500000)

/**
 * @defgroup INT_TIM int_tim
 * @{
 * @brief Internal timer that will generate interrupts to get tof sensor measurement TIM4
 * 
 */
#define INT_TIM_RCC				RCC_TIM3
#define INT_TIM					TIM3
#define INT_TIM_DIER_CCIE       TIM_DIER_CC1IE
#define INT_TIM_SR_CCIF         TIM_SR_CC1IF
/** @} */

//note: the TIM_SR_CC4OF flag is set if two interrupts occured while the first flag
//was not cleared, this can be implemented for maximum safety later. 

#define INT_TIM_OC_ID       TIM_OC1
#define INT_TIM_OC_MODE     TIM_OCM_FROZEN 
#define INT_TIM_NVIC        NVIC_TIM3_IRQ

void timer_setup_interrupt();
void tim3_isr();