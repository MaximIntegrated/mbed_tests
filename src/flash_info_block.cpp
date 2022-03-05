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
******************************************************************************/

/**
 * @file    main.c
 * @brief   Info block Dump Example
 * @details This example demonstrate how to read/write data from OTP memory
 *
 */

/***** Includes *****/
#include "mxc_tests.h"

#if  TEST_FLASH_INFO_BLOCK
#include "mbed.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "mxc_device.h"
#include "flc.h"

/***** Definitions *****/
/*
 *  Attention if you set WITH_WRITE_TEST flag
 *  This example will search INFO block and try to find 0xffffffff data
 *  If it could be found:
 *    16 test bytes (0x11223344 55667788 99AABBCC DDEEFF00) will be written in that address.
 */
#define WITH_WRITE_TEST         0   // set it to test write test

// MAXIM Info Section
#define OTP_MAXIM_AREA          MXC_INFO_MEM_BASE
#define OTP_MAXIM_AREA_SIZE     1024
// USER Info Section
#define OTP_USER_AREA           (MXC_INFO_MEM_BASE + 1024)
#define OTP_USER_AREA_SIZE      (MXC_INFO_MEM_SIZE - 1024)


/***** Static Functions *****/
static void dump_section(unsigned int address, unsigned int length)
{
    unsigned int i;
    volatile uint32_t* addr = (uint32_t*) address;

    // unlock otp to access it
    MXC_FLC_UnlockInfoBlock((uint32_t) address);

    length /= 4; // on each loop print 4 bytes

    for (i = 0; i < length; i++) {

        if (!(i % 4)) {
            printf("\n0x%08x:", (unsigned int) addr);
        }

        // add extra space
        if (!(i % 2)) {
            printf("   ");
        }

        printf(" %08x", (unsigned int)*addr);
        addr++;
    }

    // lock otp
    MXC_FLC_LockInfoBlock((uint32_t) address);
}

#if WITH_WRITE_TEST
static int write_test(void)
{
    int ret = 0;
    uint32_t test_val[]         = {0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00};
    volatile uint32_t* addr     = (uint32_t*) OTP_USER_AREA;
    volatile uint32_t* end_addr = (uint32_t*)(OTP_USER_AREA + OTP_USER_AREA_SIZE);

    // unlock otp
    MXC_FLC_UnlockInfoBlock(OTP_USER_AREA);

    // find free slot
    while (addr < end_addr) {
        if (*addr == 0xffffffff) {
            printf("\n\nFree Addr: 0x%X\n", (unsigned int) addr);
            break;
        }
        addr += 4; // align 128bit
        //addr++; // next 4 bytes
        //addr++; // next 4 bytes
        //addr++; // next 4 bytes
        //addr++; // next 4 bytes
    }

    if (addr >= end_addr) {
        ret = -1; // means free slot not found
        printf("\nFree Index Not Found in OTP\n");
    }

    if (ret == 0) {
        //ret = MXC_FLC_Write32((uint32_t) addr, test_val[0]);
        //ret = MXC_FLC_Write32((uint32_t) addr, test_val[1]);
        //ret = MXC_FLC_Write32((uint32_t) addr, test_val[2]);
        //ret = MXC_FLC_Write32((uint32_t) addr, test_val[3]);
        ret = MXC_FLC_Write((uint32_t)addr, sizeof(test_val), test_val);
        if (ret) {
            printf("FLC Write Error: %d\n", ret);
        }
    }

    // lock otp
    MXC_FLC_LockInfoBlock(OTP_USER_AREA);

    if (ret == 0) {
        /* Dump user section */
        printf("\n\n***** After Write OTP Section *****\n");
        dump_section((unsigned int) addr, 32);
    }

    return ret;
}
#endif

//******************************************************************************
int test_flash_info_block(void) 
{
    // Wait until prepare PC side,  open ports...
    ThisThread::sleep_for(5s);

    printf("\n\n***** Flash Info Memory Read/Write Example *****\n");
    printf("***** This example demonstrates how you can read/write Info memory *****\n");

    /* Dump maxim section */
    printf("\n\n***** MAXIM AREA *****\n");
    dump_section(OTP_MAXIM_AREA,    OTP_MAXIM_AREA_SIZE);

    /* Dump user section */
    printf("\n\n***** USER AREA *****\n");
    dump_section(OTP_USER_AREA,     OTP_USER_AREA_SIZE);

#if WITH_WRITE_TEST
    // run write test
    write_test();
#endif

    printf("\n\nExample End\n");

    return 0;
}
#endif // TEST_FLASH_INFO_BLOCK
