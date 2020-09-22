#include "encoder.h"

void encoder_setup(){
	/* Setup timer for ENCODER_A*/
	rcc_periph_clock_enable(ENCODER_A_RCC_TIM);
	timer_set_period(ENCODER_A_TIM, ENCODER_PERIOD);

	/*timer use special function (cf. p553 20.3.21)*/
	timer_slave_set_mode(ENCODER_A_TIM, TIM_SMCR_SMS_EM3);
	timer_ic_set_input(ENCODER_A_TIM, TIM_IC1, TIM_IC_IN_TI1);
	timer_ic_set_input(ENCODER_A_TIM, TIM_IC2, TIM_IC_IN_TI2);
	timer_direction_down(ENCODER_A_TIM);
	timer_enable_counter(ENCODER_A_TIM);

	/* Setup a_ch1 output */
	rcc_periph_clock_enable(ENCODER_A_CH1_PORT_RCC);
	gpio_mode_setup(ENCODER_A_CH1_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, ENCODER_A_CH1_PIN);
	gpio_set_af(ENCODER_A_CH1_PORT, ENCODER_A_CH1_AF, ENCODER_A_CH1_PIN);

	/* Setup a_ch2 output */
	rcc_periph_clock_enable(ENCODER_A_CH2_PORT_RCC);
	gpio_mode_setup(ENCODER_A_CH2_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, ENCODER_A_CH2_PIN);
	gpio_set_af(ENCODER_A_CH2_PORT, ENCODER_A_CH2_AF, ENCODER_A_CH2_PIN);

	/* Setup timer for ENCODER_B*/
	rcc_periph_clock_enable(ENCODER_B_RCC_TIM);
	timer_set_period(ENCODER_B_TIM, ENCODER_PERIOD);

	/*timer use special function (cf. p553 20.3.21)*/
	timer_slave_set_mode(ENCODER_B_TIM, TIM_SMCR_SMS_EM3);
	timer_ic_set_input(ENCODER_B_TIM, TIM_IC1, TIM_IC_IN_TI1);
	timer_ic_set_input(ENCODER_B_TIM, TIM_IC2, TIM_IC_IN_TI2);
	timer_direction_down(ENCODER_B_TIM);
	timer_enable_counter(ENCODER_B_TIM);

	/* Setup b_ch1 output */
	rcc_periph_clock_enable(ENCODER_B_CH1_PORT_RCC);
	gpio_mode_setup(ENCODER_B_CH1_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, ENCODER_B_CH1_PIN);
	gpio_set_af(ENCODER_B_CH1_PORT, ENCODER_B_CH1_AF, ENCODER_B_CH1_PIN);

	/* Setup b_ch2 output */
	rcc_periph_clock_enable(ENCODER_B_CH2_PORT_RCC);
	gpio_mode_setup(ENCODER_B_CH2_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, ENCODER_B_CH2_PIN);
	gpio_set_af(ENCODER_B_CH2_PORT, ENCODER_B_CH2_AF, ENCODER_B_CH2_PIN);
}

int _encoder_get_counter(enum encoder_sel sel){
	switch(sel){
		case ENCODER_A:
			if(ENCODER_A_INVERSION){
				return ENCODER_PERIOD-timer_get_counter(ENCODER_A_TIM);
			}
			return timer_get_counter(ENCODER_A_TIM);
			break;
		case ENCODER_B:
			if(ENCODER_B_INVERSION){
				return ENCODER_PERIOD-timer_get_counter(ENCODER_B_TIM);
			}
			return timer_get_counter(ENCODER_B_TIM);
			break;
	}
	return 0;
}

int encoder_update(enum encoder_sel sel, volatile int *prev_count){
	const int cnt = _encoder_get_counter(sel);

	int dl = cnt - *prev_count;
	int limit = ENCODER_PERIOD/2;
	*prev_count = cnt;
	if(dl > limit){
	  dl = dl-ENCODER_PERIOD;
	}else if(dl < -limit){
	  dl = dl+ENCODER_PERIOD;
	}
	return dl;
}
