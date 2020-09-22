#include "motor.h"

void motor_setup(){
	/* setup motor timer with a period of 20 ms 50Hz. One timer pilots
	both motors, using different channels of the output compare*/
	_timer_setup(MOTOR_TIM_RCC, MOTOR_TIM, PWM_PRESCALE, PWM_PERIOD);

	/* setup EN motor A (the PWM pin)*/
	_gpio_setup_pin_af(MOTOR_A_GPIO_RCC_EN, MOTOR_A_PORT_EN, MOTOR_A_PIN_EN, MOTOR_A_AF);
	_timer_setup_output_c(MOTOR_TIM, MOTOR_A_OC_ID, MOTOR_A_OC_MODE, 0);

	/* setup DIR motor A*/
	rcc_periph_clock_enable(MOTOR_A_GPIO_RCC_DIR);
	gpio_mode_setup(MOTOR_A_PORT_DIR, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MOTOR_A_PIN_DIR);
	gpio_set_output_options(MOTOR_A_PORT_DIR, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, MOTOR_A_PIN_DIR);
	MOTOR_A_INIT_DIR?gpio_clear(MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR):gpio_set(MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR);

	/* setup EN motor B (the PWM pin)*/
	_gpio_setup_pin_af(MOTOR_B_GPIO_RCC_EN, MOTOR_B_PORT_EN, MOTOR_B_PIN_EN, MOTOR_B_AF);
	_timer_setup_output_c(MOTOR_TIM, MOTOR_B_OC_ID, MOTOR_B_OC_MODE, 0);

	/* setup DIR motor B*/
	rcc_periph_clock_enable(MOTOR_B_GPIO_RCC_DIR);
	gpio_mode_setup(MOTOR_B_PORT_DIR, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MOTOR_B_PIN_DIR);
	gpio_set_output_options(MOTOR_B_PORT_DIR, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, MOTOR_B_PIN_DIR);
	MOTOR_B_INIT_DIR?gpio_clear(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR):gpio_set(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR);

	/* start timer */
	_timer_start(MOTOR_TIM);
}

void motor_set(enum motor_sel sel, int8_t value){
	/*value should be between -100 and +100*/
	if(value < -100 || value > 100){
		return;
	}

	int speed;
	switch(sel){
		case MOTOR_A:
			/* redefine forward direction */
			value *= MOTOR_A_INVERT_DIR;
		
			/*direction is backward: set DIR to 1 and value become positive*/
			if(value<0){
				gpio_set(MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR);
				value *= -1;
			}
			/*direction is forward: set DIR to 0*/
			else{
				gpio_clear(MOTOR_A_PORT_DIR,MOTOR_A_PIN_DIR);
			}
			/*calculate the up-time of EN between 0 and PWM_PERIOD*/
			speed = value * PWM_PERIOD/100;
			timer_set_oc_value(MOTOR_TIM, MOTOR_A_OC_ID, speed);
			break;
		case MOTOR_B:
			/* redefine forward direction */
			value *= MOTOR_B_INVERT_DIR;
		
			/*direction is backward: set DIR to 1 and value become positive*/
			if(value<0){
				gpio_set(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR);
				value *= -1;
			}
			/*direction is forward: set DIR to 0*/
			else{
				gpio_clear(MOTOR_B_PORT_DIR,MOTOR_B_PIN_DIR);
			}
			/*calculate the up-time of EN between 0 and PWM_PERIOD*/
			speed = value * PWM_PERIOD/100;
			timer_set_oc_value(MOTOR_TIM, MOTOR_B_OC_ID, speed);
			break;
	}
}
