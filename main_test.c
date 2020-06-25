#include "clock.h"
#include "motor.h"

int main(){
    
    //setup
    clock_setup();
    motor_setup();
    
    //tests
    test_motors();
}

void test_motor(){
    motor_set();
}
