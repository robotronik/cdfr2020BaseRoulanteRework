#include <stdio.h>
#include "clock.h"
#include "motor.h"
#include "uartDebug.h"
#include "encoder.h"

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
    int charReceived = 'a';
    fscanf(stderr,"%c",&charReceived);
    fprintf(stderr,"%c",charReceived);
    }
    */

    while(1){

    }
}

void test_motor(){
    motor_set(MOTOR_A,-70);
    motor_set(MOTOR_B,-45);
}

