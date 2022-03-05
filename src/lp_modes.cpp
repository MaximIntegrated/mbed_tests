
#include "mxc_tests.h"

#if  TEST_LOW_POWER_MODES
#include "mbed.h"

#include "mxc_device.h"
#include "lp.h"
#include "rtc.h"
#include "nvic_table.h"

// Used to convert RTC tick to Milisecond
#define MSEC_TO_RSSA(x) (0 - ((x * 4096) / 1000))

static DigitalOut led(LED1);
static InterruptIn button(BUTTON1);

static void button_handler(void) 
{
    led = !led;
}

static void alarmHandler(void)
{
    #if defined(TARGET_MAX32660)
        // clear flags
        MXC_RTC->ctrl &= ~(MXC_F_RTC_CTRL_ALSF);
        MXC_RTC->ctrl &= ~(MXC_F_RTC_CTRL_ALDF);
    #endif
}

static void set_rtc_alarm(unsigned int ms)
{
    while(MXC_RTC_DisableInt(MXC_RTC_INT_EN_SHORT) == E_BUSY);

    while(MXC_RTC_SetSubsecondAlarm(MSEC_TO_RSSA(ms)) == E_BUSY);

    while(MXC_RTC_EnableInt(MXC_RTC_INT_EN_SHORT) == E_BUSY);

    while(MXC_RTC_Start() == E_BUSY) {
        ;
    }
}

int test_lp_modes(void) 
{
    // Wait until prepare PC side,  open ports...
    wait_us(1*1000*1000);

    printf("\n\n---Low Power Test Cases Started---\n");

    button.rise(&button_handler);

    uint8_t port = PINNAME_TO_PORT(BUTTON1);
    uint8_t pin = PINNAME_TO_PIN(BUTTON1);

    NVIC_SetVector(RTC_IRQn, (uint32_t)alarmHandler);
    NVIC_EnableIRQ(RTC_IRQn);

    MXC_LP_EnableRTCAlarmWakeup();
    #if defined(TARGET_MAX32660)
        MXC_LP_EnableGPIOWakeup(port, 1<<pin);
    #endif

    while(1) {

        /*
         *    DEEPSLEEP MODE
         *
         */
        printf("\n\nEntering DEEPSLEEP mode.\n");
        wait_us(500*1000);  // To uart flush
        set_rtc_alarm(2000); // 2sec
        MXC_LP_ClearWakeStatus();
        MXC_LP_EnterDeepSleepMode();
        printf("Waking up from DEEPSLEEP mode\n");

    
        /*
         *    BACKUP MODE
         *
         */
        printf("\n\nEntering BACKUP mode.\n");
        wait_us(500*1000);  // To uart flush
        set_rtc_alarm(2000); // 2sec
        
        MXC_LP_ClearWakeStatus();
        
        #if defined(TARGET_MAX32660) 
            MXC_LP_EnableSRamRet0();
            MXC_LP_EnableSRamRet1();
            MXC_LP_EnableSRamRet2();
            MXC_LP_EnableSRamRet3();
        #endif
        
        MXC_LP_EnterBackupMode();
        /*
            After rtc alarm or gpio interrupt device will exit from bakup mode and will reset itself.
        */
        //printf("Waking up from BACKUP mode\n");        
    }
}
#endif // TEST_LOW_POWER_MODES
