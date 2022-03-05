/*******************************************************************************
 * Copyright (C) 2022 Maxim Integrated Products, Inc., All Rights Reserved.
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

#ifndef __MXC_TESTS_H_
#define __MXC_TESTS_H_

#define TEST_BLINK_LED          1
#define TEST_BUTTON             0
#define TEST_BUTTON_IRQ         0
#define TEST_SERIAL_READ_WRITE  0
#define TEST_SERIAL_IRQ         0
#define TEST_LP_TICKER          0
#define TEST_LOW_POWER_MODES    0
#define TEST_RTC                0
#define TEST_TIMER              0
#define TEST_DMA                0
#define TEST_WDT                0
#define TEST_FLASH_INFO_BLOCK   0

int test_blink_led(void);
int test_button(void);
int test_button_irq(void);
int test_serial_read_write(void);
int test_serial_irq(void);
int test_lp_ticker(void);
int test_lp_modes(void);
int test_rtc(void);
int test_timer(void);
int test_dma(void);
int test_wdt(void);
int test_flash_info_block(void);

#endif //__MXC_TESTS_H_
