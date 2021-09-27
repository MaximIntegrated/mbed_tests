

#include "mbed.h"

using namespace std::chrono;

static Timer t;
static Timeout flipper;
static DigitalOut led(LED1);

static int int_status = 0;

static void flip(void)
{
    led = !led;
    int_status = 1;
}

int test_timer(void)
{
    ThisThread::sleep_for(10s);
    
    printf("Timer Test\n");

    t.reset();
    t.start();
    ThisThread::sleep_for(100ms);
    t.stop();
    printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    t.reset();
    t.start();
    ThisThread::sleep_for(10ms);
    t.stop();
    printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
  
    t.reset();
    t.start();
    ThisThread::sleep_for(500ms);
    t.stop();
    printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
    
    led = 1;
    flipper.attach(&flip, 2s); // setup flipper to call flip after 2 seconds

    // spin in a main loop. flipper will interrupt it to call flip
    while (1) {
        ThisThread::sleep_for(100ms);
        
        if (int_status == 1) {
            int_status = 0;
            printf("led status changed to %d by interrupt\n", (led==1)?1:0);
            
            flipper.attach(&flip, 2s); // setup flipper to call flip after 2 seconds
        }     
    }
}
