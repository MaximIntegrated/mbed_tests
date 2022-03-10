

#include "mxc_tests.h"

#if  TEST_RTC
#include "mbed.h"

int test_rtc(void)
{
    ThisThread::sleep_for(10s);
    
    set_time(1256729737);  // Set RTC time to Wed, 28 Oct 2009 11:35:37

    time_t seconds = time(NULL);
    printf("Time as seconds since January 1, 1970 = %u\n", (unsigned int)seconds);
    
    while (true) {
        time_t seconds = time(NULL);
        printf("%s", ctime(&seconds));

        //char buffer[32];
        //strftime(buffer, 32, "%I:%M %p\n", localtime(&seconds));
        //printf("Time as a custom formatted string = %s", buffer);

        ThisThread::sleep_for(1s);
    }
}
#endif // TEST_RTC
