#include "gpio.h"

void gpio_setup_pin_af(enum rcc_periph_clken rcc_clken, uint32_t gpio_port,uint16_t gpio_pin, uint8_t gpio_altfun){
	rcc_periph_clock_enable(rcc_clken);

	gpio_mode_setup(gpio_port,GPIO_MODE_AF,GPIO_PUPD_NONE,gpio_pin);
	gpio_set_output_options(gpio_port, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, gpio_pin);     
	gpio_set_af(gpio_port, gpio_altfun, gpio_pin);
}
