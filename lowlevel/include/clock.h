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
 * @author PhenixRobotik NPXav Benano Trukbidule
*/

#pragma once

#include <stdint.h>


/**
 * @brief This function setup the system clock
 * 
 */
void clock_setup();

/**
 * @brief This function gets the number of systicks since starting
 *
 * @return    number of systicks
 */
uint32_t clock_get_systicks();

/**
 * @brief This function gets the uptime in ms
 */
//uint32_t clock_get_uptime_ms();

/**
 * @brief This function implements a delay in ms 
 * @param ms    value of delay in ms
 */
void delay_ms(uint32_t ms);
