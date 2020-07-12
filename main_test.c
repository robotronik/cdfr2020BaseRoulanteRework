#include <stdio.h>
#include "clock.h"
#include "motor.h"
#include "encoder.h"
#include "uart.h"

void test_motor();

int main(){
    
    //setup
    clock_setup();
    //motor_setup();
    uart_setup();
    encoder_setup();
    
    //tests
    // TEST Benano
    while(1){
    fprintf(stderr,"coucou sur le debug \n");
    delay_ms(500);
    test_send_comm_usart();
    delay_ms(500);
    }
    

}

void test_motor(){
    motor_set(MOTOR_A,-70);
    motor_set(MOTOR_B,-45);
}


void test_send_comm_usart(){
  fprintf(stderr,"sending a char 'c'");
  fprintf(stdout,"c");
  fprintf(stderr,"sending a string : hello");
  fprintf(stdout,"hello"); 

}
