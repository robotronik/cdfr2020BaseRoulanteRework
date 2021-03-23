#include <stdio.h>
#include "clock.h"
#include "motor.h"
#include "encoder.h"
#include "uart.h"
#include "timer_int.h"

void test_motor();
void test_send_comm_usart();
void test_interrupt_timer();
void blink_led();

int main(){
    
    //setup
    clock_setup();
    uart_setup();

    // blink_led();
    // test_encoder();
    // test_motor();
    // test_send_comm_usart();
    test_interrupt_timer();
}

void blink_led(){     //led is on PB3     
    _gpio_setup_pin(LED_GPIO_RCC,LED_GPIO_PORT,LED_GPIO_PIN,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);          
    while(1){         
        gpio_toggle(LED_GPIO_PORT,LED_GPIO_PIN);
        delay_ms(200);     
    } 
}

void test_encoder(){
    encoder_setup();

    volatile int counterLeft;
    volatile int counterRight;

    //encoder testing
    while(1){
        encoder_update(ENCODER_A,&counterLeft);
        encoder_update(ENCODER_B,&counterRight);
        fprintf(stderr,"counterLeft=%d \t counterRight=%d \n",counterLeft,counterRight);
        delay_ms(100);
    }
}

void test_motor(){
    motor_setup();

    motor_set(MOTOR_A,-70);
    motor_set(MOTOR_B,-45);
}


void test_send_comm_usart(){
  uint16_t myInt = 20;
  fprintf(stderr,"sending a int: %d \n",myInt);
  //usart_send_blocking(COMM_USART,myInt);
  fprintf(stdout,"%d",myInt);
  // fprintf(stderr,"sending a string : hello\n");
  // fprintf(stdout,"hello"); 

}

void test_interrupt_timer(){
    _gpio_setup_pin(LED_GPIO_RCC,LED_GPIO_PORT,LED_GPIO_PIN,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);          

    timer_setup_interrupt();
    while (1);
}        
