#include <stdio.h>
#include "clock.h"
#include "motor.h"
#include "uartDebug.h"

void test_motor();

int main(){
    
    //setup
    clock_setup();
    //motor_setup();
    uart_setup();
    
    //tests
    while(1){
    fprintf(stderr,"coucou sur le debug \n");
    }
}

void test_motor(){
    motor_set(MOTOR_A,-70);
    motor_set(MOTOR_B,-45);
}
