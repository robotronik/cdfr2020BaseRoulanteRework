/**
 * @file
 * 
 * This file is part of cdfr2020BaseRoulanteRework
 * 
 * @brief This implements the setup of the encoders and the counting  
 * 
 * @date  06/2020  
 * 
 * Licence :
 * 
 * Robotronik Phelma
 * @author PhenixRobotik NPXav Benano Trukbidule
 */

#pragma once

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

/**
 * number of ticks per turn, encoder 300CPR 
 */
#define ENCODER_PERIOD (300*4-1)

/**
 * @defgroup ENCODER_A encoder_a
 * @{
 * @brief Definition for ENCODER_A
 *
 * Using one timer and 2 channel for quadrature
 */
#define ENCODER_A_RCC_TIM RCC_TIM1
#define ENCODER_A_TIM TIM1

#define ENCODER_A_INVERSION 0

#define ENCODER_A_CH1_PORT GPIOA
#define ENCODER_A_CH1_PORT_RCC RCC_GPIOA
#define ENCODER_A_CH1_AF GPIO_AF6
#define ENCODER_A_CH1_PIN GPIO8

#define ENCODER_A_CH2_PORT GPIOA
#define ENCODER_A_CH2_PORT_RCC RCC_GPIOA
#define ENCODER_A_CH2_AF GPIO_AF6
#define ENCODER_A_CH2_PIN GPIO9
/** @} */

/**
 * @defgroup ENCODER_B encoder_b
 * @{
 * @brief Definition for ENCODER_B
 *
 * Using one timer and 2 channel for quadrature
 */
#define ENCODER_B_RCC_TIM RCC_TIM2
#define ENCODER_B_TIM TIM2

#define ENCODER_B_INVERSION 0

#define ENCODER_B_CH1_PORT GPIOA
#define ENCODER_B_CH1_PORT_RCC RCC_GPIOA
#define ENCODER_B_CH1_AF GPIO_AF1
#define ENCODER_B_CH1_PIN GPIO0

#define ENCODER_B_CH2_PORT GPIOA
#define ENCODER_B_CH2_PORT_RCC RCC_GPIOA
#define ENCODER_B_CH2_AF GPIO_AF1
#define ENCODER_B_CH2_PIN GPIO1
/** @} */

/**
 * @brief enum of the two encoders of the robot to choose which one will be used
 * 
 */
enum encoder_sel {ENCODER_A, ENCODER_B};

/**
 * @brief This function initialize the timers and GPIOs used for each encoder
 *
 */
void encoder_setup();

/**
 * @brief get the actual counter on selected encoder
 * 
 * @param sel    the encoder for which the counter is read
 * @return    actual counter on selected encoder
 */
int _encoder_get_counter(enum encoder_sel sel);

/**
 * @brief delta steps in small time difference
 * 
 * @param sel    the encoder that is updated
 * @param prev_count    pointer on the previous
 * @return    delta value (difference between actual and previous)
 */
int encoder_update(enum encoder_sel sel, volatile int *prev_count);
