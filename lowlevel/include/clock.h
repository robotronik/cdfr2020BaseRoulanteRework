/**
 * @file
 * 
 * This file is part of cdfr2020BaseRoulanteRework
 * 
 * @brief This implements the setup of the system clock, acces fonction (debug) and temporal fonction (delay)  
 * 
 * @date  06/2020  
 * 
 * Licence :
 * 
 * Robotronik Phelma
 * @author Ancien NPXav Benano Trukbidule
*/

#pragma once
#include <stdint.h>

/**
 * RCC Clock Frequency [Hz]
 */
#define RCC_CLOCK_FREQ_HZ (     64000000)

/**
 * Interruptions = 10kHz = 100us (beaucoup ?)
 */
#define SYSTICK_FREQ_HZ   (       100000)
#define SYSTICK_PERIOD    (RCC_CLOCK_FREQ_HZ / SYSTICK_FREQ_HZ)


#define MICROS_SYSTICK_RATIO (1000000 / SYSTICK_FREQ_HZ)

#define MILLIS_TO_SYSTICK(ms) (ms * 1000 / MICROS_SYSTICK_RATIO)
#define SYSTICK_TO_MILLIS(ticks) (ticks * MICROS_SYSTICK_RATIO / 1000)

/**
 * @brief This function setup the system clock
 * 
 */
void clock_setup();

/**
 * @brief This function gets the number of systicks since starting
 */
uint32_t clock_get_systicks();

/**
 * @brief This function gets the uptime in ms
 */
uint32_t clock_get_uptime_ms();

/**
 * @brief This function implements a delay in ms 
 * @param ms    value of delay in ms
 */
void delay_ms(uint32_t ms);
