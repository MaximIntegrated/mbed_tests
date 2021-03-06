/*******************************************************************************
 * Copyright (C) Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 *
 ******************************************************************************/

#include "mbed.h"
#include "mxc_tests.h"

int main(void)
{
    #if  TEST_BLINK_LED
        test_blink_led();
    #elif TEST_BUTTON
        test_button();
    #elif TEST_BUTTON_IRQ
        test_button_irq();
    #elif TEST_SERIAL_READ_WRITE
        test_serial_read_write();
    #elif TEST_SERIAL_IRQ
        test_serial_irq();
    #elif TEST_RTC
        test_rtc();
    #elif TEST_TIMER
        test_timer();
    #elif TEST_LP_TICKER
        test_lp_ticker();
    #elif TEST_DMA
        test_dma();
    #elif TEST_WDT
        test_wdt();
    #elif TEST_LOW_POWER_MODES
        test_lp_modes();
    #elif TEST_FLASH_INFO_BLOCK
        test_flash_info_block();
    #endif
}
