

#include "mbed.h"
    
static DigitalOut led(LED1);
static DigitalIn  button(BUTTON1);
 
int test_button(void)
{
    led = 0;
    while(1) {
        if (button.read() == 1) {
            if (led == 0) {
                led = 1;
                printf("Button status changed to 1\n");
            }
        } else {
            if (led == 1) {
                led = 0;
                printf("Button status changed to 0\n");
            }
        }
        ThisThread::sleep_for(10ms);
    }
}
