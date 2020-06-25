#include "timer.h"

void timer_setup(enum rcc_periph_clken rcc_clken, uint32_t timer_peripheral, uint32_t prescaler, uint32_t period){
	/* Enable timer clock. */
	//rcc_peripheral_enable_clock(reg, en); version online
	rcc_periph_clock_enable(rcc_clken);
    
	/* Reset TIM1 peripheral */
	//timer_reset(timer_peripheral);

	/* Set the timers global mode to:
	 * - use no divider
	 * - alignment edge
	 * - count direction up
	 */
	timer_set_mode(timer_peripheral,
	               TIM_CR1_CKD_CK_INT,
	               TIM_CR1_CMS_EDGE,
	               TIM_CR1_DIR_UP);

	timer_set_prescaler(timer_peripheral, prescaler);
	timer_set_repetition_counter(timer_peripheral, 0);
	timer_enable_preload(timer_peripheral);
	timer_continuous_mode(timer_peripheral);
	timer_set_period(timer_peripheral, period);
}

void timer_setup_output_c(uint32_t timer_peripheral, enum tim_oc_id oc_id, enum tim_oc_mode oc_mode, uint32_t oc_value){
	timer_disable_oc_output(timer_peripheral, oc_id);
	timer_set_oc_mode(timer_peripheral, oc_id, oc_mode);
	timer_enable_oc_preload(timer_peripheral, oc_id);
	timer_set_oc_value(timer_peripheral, oc_id, oc_value);
	timer_enable_oc_output(timer_peripheral, oc_id);
}
