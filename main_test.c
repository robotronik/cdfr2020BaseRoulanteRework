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

    //test_motor();
    // uart_send_string("Hello \r\n");
    // delay_ms(5000);
   	// uart_send_string("THIS \r\n");
    // uart_send_string("IS \r\n");
    // uart_send_string("ME \r\n");
    // uart_send_string("MARIO \r\n");

    int intrcvd = -1;
    while(1){
    uart_send_string("super nul\n");
    fprintf(stderr,"coucou sur le debug \n");

    // int nul = usart_recv_blocking(DEBUG_USART);
    // printf("boring int received = %d",nul);

    fscanf(stderr,"%c",intrcvd);
    fprintf(stderr,"char received = %c",intrcvd);
    }
}

void test_motor(){
    motor_set(MOTOR_A,-70);
    motor_set(MOTOR_B,-45);
}
