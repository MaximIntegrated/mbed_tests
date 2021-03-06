

#include "mxc_tests.h"

#if  TEST_WDT
#include "mbed.h"

static const uint32_t TIMEOUT_MS = 5000;
static InterruptIn button(BUTTON1);
static volatile int countdown = 10;

static void trigger(void)
{
    Watchdog::get_instance().kick();
    countdown = 10;
}

int test_wdt(void)
{
    printf("\r\nTarget started.\r\n");

    Watchdog &watchdog = Watchdog::get_instance();
    watchdog.start(TIMEOUT_MS);
    button.rise(&trigger);

    uint32_t watchdog_timeout = watchdog.get_timeout();
    printf("Watchdog initialized to %lu ms.\r\n", watchdog_timeout);
    printf("Press BUTTON1 at least once every %lu ms to kick the "
           "watchdog and prevent system reset.\r\n", watchdog_timeout);

    unsigned int delay = watchdog_timeout / countdown;
    while (1) {
        printf("\r%3i ", --countdown);
        fflush(stdout);
        ThisThread::sleep_for(delay);
    }
}
#endif // TEST_WDT
