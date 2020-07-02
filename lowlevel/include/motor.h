/**
 * @file
 * 
 * This file is part of cdfr2020BaseRoulanteRework
 * 
 * @brief This implements the functions required to pilot the propulsion motors of the robot  
 * 
 * @date  06/2020  
 * 
 * Licence :
 * 
 * Robotronik Phelma
 * @author NPXav Benano Trukbidule
*/

#pragma once
#include <libopencm3/stm32/timer.h>

#include "timer.h"
#include "gpio.h"

/**
 * Prescale 64000000 Hz system clock by 64 = 1000000 Hz.
 */
#define PWM_PRESCALE	(64)

/**
 * We need a 50 Hz period (1000 / 20ms = 50), thus divide 100000 by 50 = 20000 (us).
 */
#define PWM_PERIOD		(20000)


/**
 * @defgroup MOTOR_TIM motor_tim
 * @{
 * @brief Internal timer used to pilot the motors
 * 
 * Two channels are used for the MOTOR_A and MOTOR_B
 */
#define MOTOR_TIM_RCC				RCC_TIM3
#define MOTOR_TIM					TIM3
/** @} */

/**
 * @defgroup MOTOR_A motor_a
 * @{
 * @brief Definition for the MOTOR_A
 *
 * EN stand for enable (output of the PWM signal) \n
 * We use OC_ID to use a specific channel as a PWM_output \n
 * DIR stand for direction (boolean value) \n
 * INIT_DIR is the initial direction of the motor
 */
#define MOTOR_A_GPIO_RCC_EN			RCC_GPIOA
#define MOTOR_A_PORT_EN				GPIOA
#define MOTOR_A_PIN_EN				GPIO4

#define MOTOR_A_AF					GPIO_AF2
#define MOTOR_A_OC_ID				TIM_OC2
#define MOTOR_A_OC_MODE				TIM_OCM_PWM1

#define MOTOR_A_GPIO_RCC_DIR		RCC_GPIOA
#define MOTOR_A_PORT_DIR			GPIOA
#define MOTOR_A_PIN_DIR				GPIO3

#define MOTOR_A_INIT_DIR			0
/** @} */

/**
 * @defgroup MOTOR_B motor_b
 * @{
 * @brief Definition for the MOTOR_B
 *
 * EN stand for enable (output of the PWM signal) \n
 * We use OC_ID to use a specific channel as a PWM_output \n
 * DIR stand for direction (boolean value) \n
 * INIT_DIR is the initial direction of the motor
 */
#define MOTOR_B_GPIO_RCC_EN			RCC_GPIOA
#define MOTOR_B_PORT_EN				GPIOA
#define MOTOR_B_PIN_EN				GPIO6

#define MOTOR_B_AF					GPIO_AF2
#define MOTOR_B_OC_ID				TIM_OC1
#define MOTOR_B_OC_MODE				TIM_OCM_PWM1

#define MOTOR_B_GPIO_RCC_DIR		RCC_GPIOA
#define MOTOR_B_PORT_DIR			GPIOA
#define MOTOR_B_PIN_DIR				GPIO7

#define MOTOR_B_INIT_DIR			0
/** @} */

/**
 * @brief enum of the two motors of the robot to choose which one will be piloted (with function motor_set)
 * 
 */
enum motor_sel {MOTOR_A, MOTOR_B};

/**
 * @brief This function initialize the timers and GPIOs to pilot the propulsion motors in our setup by PWM + the GPIOs for the direction
 * 
 */
void motor_setup();

/**
 * @brief This function pilot the sel (MOTOR_A or MOTOR_B) with a value between -100(backward full speed) and +100 (forward full speed)
 * 
 * @param sel    The motor that will be piloted (eg MOTOR_A) 
 * @param value    value is between -100 and +100, controls the speed and direction of the motor sel (eg +54)
 * @todo we choose that 0 is forward and 1 is backward, it should be defined in a macro and adjustable for the motors
 */
void motor_set(enum motor_sel sel, int8_t value);
