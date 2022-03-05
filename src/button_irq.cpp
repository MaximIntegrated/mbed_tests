
#include "mxc_tests.h"

#if  TEST_BUTTON_IRQ
#include "mbed.h"

static DigitalOut  led(LED1);
static InterruptIn button(BUTTON1);

static int int_status = 0;

static void toogle_led(void) 
{
    led = !led;
    int_status = 1;
}
 
int test_button_irq(void) 
{
    button.rise(&toogle_led);
    while(1) {
        ThisThread::sleep_for(100ms);
        
        if (int_status == 1) {
            int_status = 0;
            printf("led status changed to %d by interrupt\n", (led==1)?1:0);
        }           
    }
}
#endif // TEST_BUTTON_IRQ
