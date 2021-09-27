

#include "mbed.h"


static LowPowerTicker flipper;
static DigitalOut     led(LED1);

static void flip(void)
{
    led = !led;
}

int test_lp_ticker(void)
{
    led = 1;
    flipper.attach(&flip, 2s);

    while (1) {
        ThisThread::sleep_for(200ms);
        //wait_us(200*1000); 
    }
}
