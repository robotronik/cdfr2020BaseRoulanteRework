#include "uartDebug.h"


void uart_setup()
{
	// Open GPIO for USART
	rcc_periph_clock_enable(DEBUG_PORT_TX_RCC);
	gpio_mode_setup(DEBUG_PORT_TX, GPIO_MODE_AF, GPIO_PUPD_NONE, DEBUG_PIN_TX);
	gpio_set_af(DEBUG_PORT_TX, DEBUG_AF_TX, DEBUG_PIN_TX);

	//rcc_periph_clock_enable(DEBUG_PORT_RX_RCC);
	gpio_mode_setup(DEBUG_PORT_RX, GPIO_MODE_AF, GPIO_PUPD_NONE, DEBUG_PIN_RX);
	gpio_set_af(DEBUG_PORT_RX, DEBUG_AF_RX, DEBUG_PIN_RX);

	rcc_periph_clock_enable(DEBUG_RCC_USART);

	usart_disable(DEBUG_USART);

	usart_set_baudrate(DEBUG_USART, DEBUG_UART_SPEED);
	usart_set_databits(DEBUG_USART, 8);
	usart_set_stopbits(DEBUG_USART, USART_STOPBITS_1);
	usart_set_mode(DEBUG_USART, USART_MODE_TX_RX);
	usart_set_parity(DEBUG_USART, USART_PARITY_NONE);
	usart_set_flow_control(DEBUG_USART, USART_FLOWCONTROL_NONE);

	usart_enable(DEBUG_USART);
  setbuf(stdout,NULL); //necessary for printf
}

void uart_send_string(char* chain)
{
  for (int i = 0; chain[i] != 0; i++) {
    usart_send_blocking(DEBUG_USART, chain[i]);
  }
}


void uart_send_string_formatted_v(const char *fmt, va_list argp)
{
    char string[80];
    if (vsprintf(string, fmt, argp) <= 0)
      return;

    uart_send_string(string);
}

void uart_send_string_formatted(const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  uart_send_string_formatted_v(fmt, argp);
  va_end(argp);
}

void uart_send_int(int integer)
{
	int i = 0,
      total_digits = 0,
      integer_tmp = integer;
	char chain[256], *chain_tmp;

  // add - before if negative number
	if(integer < 0)
	{
		chain[0] = '-';
		chain_tmp = &chain[1];
    // absolute value
		integer = -integer;
	}
	else
	{
		chain_tmp = chain;
	}

	// the power of ten of the number
	do{
		integer_tmp /= 10;
		total_digits++;
	} while(integer_tmp != 0);

  // converting the integer to caracters
	do{
		chain_tmp[total_digits - i - 1] = (integer % 10) + '0';
		i++;
		integer /= 10;
	} while(integer != 0);

  // end of number line
	chain_tmp[i]='\0';
  // finally prints the number
	uart_send_string(chain);
}

// www.rhyne.org
int _write(int file, const char *ptr, ssize_t len) {
    // If the target file isn't stdout/stderr, then return an error
    // since we don't _actually_ support file handles
    if (file != STDOUT_FILENO && file != STDERR_FILENO) {
        // Set the errno code (requires errno.h)
        errno = EIO;
        return -1;
    }

    // Keep i defined outside the loop so we can return it
    int i;
    for (i = 0; i < len; i++) {
        // If we get a newline character, also be sure to send the carriage
        // return character first, otherwise the serial console may not
        // actually return to the left.
        if (ptr[i] == '\n') {
            usart_send_blocking(DEBUG_USART, '\r');
        }

        // Write the character to send to the USART1 transmit buffer, and block
        // until it has been sent.
        usart_send_blocking(DEBUG_USART, ptr[i]);
    }

    // Return the number of bytes we sent
    return i;
}