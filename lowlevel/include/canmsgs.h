/**
 * @file
 *
 * This file is part of cdfr2020BaseRoulante
 *
 * @brief This implements the setup of communication between F3, F4 and other
 *        potential computers using CAN protocol.
 *		  Source: https://www.rhye.org/post/stm32-with-opencm3-3-canbus/
 * @date  10/2020
 *
 * Licence :
 *
 * Robotronik Phelma
 * @author NPXav Benano Trukbidule JamesWright Floorcows KameradJS(Nornort)
 */

#pragma once

#include "gpio.h"

/* #include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> */

#include <stdio.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/can.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>


// can clock is on APB1, there is a /2 prescaler compared to cpu clock
// this means you have to do calculations with a 42MHz clock for the CAN peripheral
// TODO: check if the prescale comes fromp APB or AHB

//// Bit timing settings
//// http://www.bittiming.can-wiki.info/
// Setting is currently 400 kbit/s CAN_BTR should be 0x001c0004
// Resync time quanta jump width
#define PARAM_SJW CAN_BTR_SJW_1TQ
// Time segment 1 time quanta width
#define PARAM_TS1 CAN_BTR_TS1_13TQ 
// Time segment 2 time quanta width
#define PARAM_TS2 CAN_BTR_TS2_2TQ 
// Baudrate prescaler
#define PARAM_BRP 5
// sample point 87.5

#define CAN1_RX_PORT GPIOA
#define CAN1_RX_PIN GPIO11
#define CAN1_RX_RCC RCC_GPIOA
#define CAN1_RX_AF GPIO_AF9
//#define CAN CAN1 ID ??
#define CAN1_TX_PORT GPIOA
#define CAN1_TX_PIN GPIO12
#define CAN1_TX_RCC RCC_GPIOA
#define CAN1_TX_AF GPIO_AF9

/**
 * @brief Startup configuration of the CAN system
 *
 */
void can_setup();

void can1_rx1_isr(); // Interupt Routine FIFO1
void usb_lp_can1_rx0_isr(); // Interupt Routine FIFO0
void can1_sce_isr(); // Status Change and Error Routine