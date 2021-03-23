#include "timer_int.h"

volatile int res;
volatile int i = 0;

void timer_setup_interrupt(){
    _timer_setup(INT_TIM_RCC,INT_TIM,INT_TIM_PRESCALER,INT_TIM_PERIOD);
    
    nvic_enable_irq(INT_TIM_NVIC);
    timer_enable_irq(INT_TIM,TIM_DIER_UIE);

    _timer_start(INT_TIM);
}

void tim3_isr(){
    if (timer_get_flag(INT_TIM, TIM_SR_UIF))
	{
        //do something
        timer_clear_flag(INT_TIM, TIM_SR_UIF);
        timer_get_flag(INT_TIM, TIM_SR_UIF);
        
        i++;
        res += i;
        fprintf(stderr,"interrupt from timer! i : %d res: %d\n",i,res);
        gpio_toggle(LED_GPIO_PORT,LED_GPIO_PIN);		
	}
}
