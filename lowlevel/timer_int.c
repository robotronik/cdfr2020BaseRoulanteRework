#include "timer_int.h"

void timer_setup_interrupt(){
    _timer_setup(INT_TIM_RCC,INT_TIM,INT_TIM_PRESCALE,INT_TIM_PERIOD);
    _timer_setup_output_c(INT_TIM,INT_TIM_OC_ID,INT_TIM_OC_MODE,0);
    //timer_disable_oc_clear(INT_TIM, INT_TIM_OC_ID);
    //timer_disable_preload(INT_TIM);
    //timer_set_oc_slow_mode(INT_TIM, INT_TIM_OC_ID);
    nvic_enable_irq(INT_TIM_NVIC);
	timer_enable_irq(INT_TIM, INT_TIM_DIER_CCIE);
    _timer_start(INT_TIM);
}

void tim3_isr(){
    if (timer_get_flag(INT_TIM, INT_TIM_SR_CCIF))
	{
        //do something
        fprintf(stderr,"interrupt from timer\n");
        gpio_toggle(LED_GPIO_PORT,LED_GPIO_PIN);

		timer_clear_flag(INT_TIM, INT_TIM_SR_CCIF);
	}
}
