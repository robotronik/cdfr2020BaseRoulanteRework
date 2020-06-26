#include "clock.h"
#include "motor.h"

void test_motor();

int main(){
    
    //setup
    clock_setup();
    motor_setup();
    
    //tests
    test_motor();
}

void test_motor(){
    motor_set(MOTOR_A,-70);
    motor_set(MOTOR_B,-45);
}
