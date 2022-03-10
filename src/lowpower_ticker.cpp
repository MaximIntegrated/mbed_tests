
#include "mxc_tests.h"

#if  TEST_LP_TICKER
#if DEVICE_LPTICKER
#include "mbed.h"

using namespace std::chrono;

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
#endif // DEVICE_LPTICKER

#endif // TEST_LP_TICKER
