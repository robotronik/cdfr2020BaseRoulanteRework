#pragma once

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>


/***************************************
simple uart configuration for debugging
***************************************/

// DEFINES FOR DEBUG_UART
#define DEBUG_RCC_USART RCC_USART2
#define DEBUG_USART USART2
#define DEBUG_UART_SPEED (9600) // I AM SPEED

#define DEBUG_PORT_TX GPIOA
#define DEBUG_PORT_TX_RCC RCC_GPIOA
#define DEBUG_PIN_TX GPIO2 //on veut essayer PA14
#define DEBUG_AF_TX GPIO_AF7

#define DEBUG_PORT_RX GPIOA
#define DEBUG_PORT_RX_RCC RCC_GPIOA
#define DEBUG_PIN_RX GPIO15 // on veut essayer PA15
#define DEBUG_AF_RX GPIO_AF7


#define COMM_RCC_USART RCC_USART1
#define COMM_USART USART1
#define COMM_UART_SPEED (9600)

#define COMM_PORT_TX GPIOB
#define COMM_PORT_TX_RCC RCC_GPIOB 
#define COMM_PIN_TX GPIO6
#define COMM_AF_TX GPIO_AF7

#define COMM_PORT_RX GPIOB
#define COMM_PORT_RX_RCC RCC_GPIOB
#define COMM_PIN_RX GPIO7
#define COMM_AF_RX GPIO_AF7



void uart_setup();
void uart_send_string(char* chain); // NULL-ended string
void uart_send_int(int integer);

// Warning : hard-limit on string length to 80 chars
void uart_send_string_formatted(const char *fmt, ...);

//rec=usart_recv_blocking(DEBUG_USART);//to receive a byte

int _write(int file, const char *ptr, ssize_t len);