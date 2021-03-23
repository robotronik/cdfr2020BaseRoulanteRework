#include <stdio.h>
#include "clock.h"
#include "motor.h"
#include "encoder.h"
#include "uart.h"

void test_motor();
void test_send_comm_usart();
void blink_led();
int main(){
    
    //setup
    clock_setup();
    //motor_setup();
    //uart_setup();
    //encoder_setup();
    

    volatile int counterLeft;
    volatile int counterRight;

    //tests
    // TEST Benano
    /*
    while(1){
    //fprintf(stderr,"coucou sur le debug \n");
    //delay_ms(200);
    // int charReceived = 'a';
    // fscanf(stderr,"%c",&charReceived);
    // fprintf(stderr,"%c",charReceived);
    // test_send_comm_usart();
    // delay_ms(1000);
    //delay_ms(500);
    //test_send_comm_usart();
    //delay_ms(500);
    
    //encoder testing
    encoder_update(ENCODER_A,&counterLeft);
    encoder_update(ENCODER_B,&counterRight);
    fprintf(stderr,"counterLeft=%d \t counterRight=%d \n",counterLeft,counterRight);
    }
    */

    blink_led();
    

}

void blink_led(){     //led is on PB3     
    _gpio_setup_pin(RCC_GPIOB,GPIOB,GPIO3,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_OTYPE_PP);          
    while(1){         
        gpio_toggle(GPIOB,GPIO3);
        delay_ms(200);     
    } 
}

void test_motor(){
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
        
