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
    /* TEST Benano
    while(1){
    fprintf(stderr,"coucou sur le debug \n");
    delay_ms(200);
    // int charReceived = '-1';
    // fscanf(stderr,"%c",&charReceived);
    // fprintf(stderr,"%c",charReceived);
    // test_send_comm_usart();
    // delay_ms(1000);
    }
    */

    while(1){

    }
}

void test_motor(){
    motor_set(MOTOR_A,-70);
    motor_set(MOTOR_B,-45);
}


void test_send_comm_usart(){
  fprintf(stderr,"sending a char 'c'");
  char myChar = 'c';
  fprintf(stdout,"%c",myChar);
  fprintf(stderr,"sending a string : hello");
  fprintf(stdout,"hello"); 

}
