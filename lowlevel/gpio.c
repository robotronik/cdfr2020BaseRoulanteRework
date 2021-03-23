#include "gpio.h"

void _gpio_setup_pin_af(enum rcc_periph_clken rcc_clken, uint32_t gpio_port,
        uint16_t gpio_pin, uint8_t gpio_altfun,uint8_t pull_up_down,uint8_t otype){
	/* Enable clock on port*/
	rcc_periph_clock_enable(rcc_clken);

	/* Setup pin as altfun and no pull up or pull down */
	gpio_mode_setup(gpio_port,GPIO_MODE_AF,pull_up_down,gpio_pin);
	
	/* Setup pin as push-pull with a default speed of 50 MHz */
	gpio_set_output_options(gpio_port, otype,GPIO_OSPEED_50MHZ, gpio_pin); 

	/* Setup alternate function */    
	gpio_set_af(gpio_port, gpio_altfun, gpio_pin);
}

void _gpio_setup_pin(enum rcc_periph_clken clken, uint32_t port,uint16_t pin,
        uint8_t mode, uint8_t pull_up_down,uint8_t otype){
    rcc_periph_clock_enable(clken);
	/* Setup pin as input or output and no pull up or pull down */
    gpio_mode_setup(port,mode,pull_up_down,pin);

    if(mode==GPIO_MODE_OUTPUT){
	gpio_set_output_options(port, otype,GPIO_OSPEED_50MHZ, pin); 
    }
}

void __pulse(uint32_t port, uint16_t pin, uint8_t dir, uint16_t delay){
    // IDLE High, pulse direction : falling
	if(!dir){
		gpio_clear(port,pin);
		delay_ms(delay);
		gpio_set(port,pin);
	}
	// IDLE Low, pulse direction : rising
	else{
		gpio_set(port,pin);
		delay_ms(delay);
		gpio_clear(port,pin);
	}
}


