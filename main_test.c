#include "clock.h"
#include "motor.h"
#include "uartDebug.h"

void test_motor();

int main(){
    
    //setup
    clock_setup();
    motor_setup();
    uart_setup();
    
    
    //tests
    test_motor();
	
    while(1){
    	uart_send_string("Hello World \n");
    }
}

void test_motor(){
    motor_set(MOTOR_A,-70);
    motor_set(MOTOR_B,-45);
}
