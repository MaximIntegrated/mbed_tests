

#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

int test_blink_led(void)
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        printf("Hello World!\n");
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
       //wait_us(5000*100); 
    }
}
