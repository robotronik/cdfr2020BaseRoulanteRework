#include "motor.h"

void motor_setup(){
	/* setup motor timer with a period of 20 ms*/
	timer_setup(MOTOR_TIM_RCC, MOTOR_TIM, PWM_PRESCALE, PWM_PERIOD);

	/* setup en motor a*/
	gpio_setup_pin_af(MOTOR_A_GPIO_RCC_EN, MOTOR_A_PORT_EN, MOTOR_A_PIN_EN, MOTOR_A_AF);
	timer_setup_output_c(MOTOR_TIM, MOTOR_A_OC_ID, MOTOR_A_OC_MODE, 0);

	/* setup dir motor a*/
	rcc_periph_clock_enable(MOTOR_A_GPIO_RCC_DIR);
	gpio_mode_setup(MOTOR_A_PORT_DIR, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MOTOR_A_PIN_DIR);
	gpio_set_output_options(MOTOR_A_PORT_DIR, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, MOTOR_A_PIN_DIR);

	/* setup en motor b*/
	gpio_setup_pin_af(MOTOR_B_GPIO_RCC_EN, MOTOR_B_PORT_EN, MOTOR_B_PIN_EN, MOTOR_B_AF);
	timer_setup_output_c(MOTOR_TIM, MOTOR_B_OC_ID, MOTOR_B_OC_MODE, 0);

	/* setup dir motor b*/
	rcc_periph_clock_enable(MOTOR_B_GPIO_RCC_DIR);
	gpio_mode_setup(MOTOR_B_PORT_DIR, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MOTOR_B_PIN_DIR);
	gpio_set_output_options(MOTOR_B_PORT_DIR, GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ, MOTOR_B_PIN_DIR);

	/* start timer */
	timer_start(MOTOR_TIM);
}
