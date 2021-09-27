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
 * @file        main.c
 * @brief       DMA Example
 * @details     This runs through two DMA examples, first being memory-to-memory,
 *              second being a transfer with reload and callback.
 */


/*******************************      INCLUDES    ****************************/
#include "mbed.h"
#include "dma.h"

/*******************************      DEFINES     ****************************/
#define MAX_SIZE    64

/******************************* Type Definitions ****************************/


/*******************************    Variables     ****************************/
static int g_dma_ch = -1;
static volatile int g_int_flag = 0;

/******************************* Static Functions ****************************/
static void my_int_func(int a, int b)
{
    int flags;
    flags = MXC_DMA_ChannelGetFlags(g_dma_ch);
    MXC_DMA_ChannelClearFlags(g_dma_ch, flags);
}

static void memCpyComplete(void* dest)
{
    g_int_flag++;
}

static void DMAx_IRQHandler(void)
{
    MXC_DMA_Handler();
}

static int dma_example_mem2mem(void)
{
    int retval = E_NO_ERROR;
    printf("\nTransfer from memory to memory.\n");

    uint8_t srcdata[MAX_SIZE];
    uint8_t dstdata[MAX_SIZE];

    //Initialize data before transfer
    for (int i = 0; i < MAX_SIZE; ++i) {
        srcdata[i] = i;
        dstdata[i] = 0;
    }

    g_int_flag = 0;
    MXC_DMA_MemCpy(dstdata, srcdata, MAX_SIZE, memCpyComplete);
    while(g_int_flag == 0) {
        ;
    }
    
    //Validate
    if (memcmp(srcdata, dstdata, MAX_SIZE) != 0) {
        printf("Data mismatch.\n");
        retval = -1;
    } else {
        printf("Data verified.\n");
    }

    return retval;
}

static int dma_example_mem2mem_with_reload(void)
{
    int retval = E_NO_ERROR;
    printf("\nTransfer with Reload and Callback.\n");
    
    uint8_t srcdata[MAX_SIZE];
    uint8_t dstdata[MAX_SIZE]; 
    uint8_t srcdata2[MAX_SIZE];
    uint8_t dstdata2[MAX_SIZE];

    //Init data
    for (int i = 0; i < MAX_SIZE; ++i) {
        srcdata[i] = i;
        dstdata[i] = 0;
        //Different set of data
        srcdata2[i] = MAX_SIZE-1-i;
        dstdata2[i] = 0;
    }

    g_dma_ch = MXC_DMA_AcquireChannel();

    mxc_dma_srcdst_t firstTransfer;
    firstTransfer.ch = g_dma_ch;
    firstTransfer.source = srcdata;
    firstTransfer.dest = dstdata;
    firstTransfer.len = MAX_SIZE;

    mxc_dma_config_t config;
    config.ch = g_dma_ch;
    config.reqsel = MXC_DMA_REQUEST_MEMTOMEM;
    config.srcwd = MXC_DMA_WIDTH_WORD;
    config.dstwd = MXC_DMA_WIDTH_WORD;
    config.srcinc_en = 1;
    config.dstinc_en = 1;

    mxc_dma_adv_config_t advConfig;
    advConfig.ch = g_dma_ch;
    advConfig.prio = MXC_DMA_PRIO_HIGH;
    advConfig.reqwait_en = 0;
    advConfig.tosel = MXC_DMA_TIMEOUT_4_CLK;
    advConfig.pssel = MXC_DMA_PRESCALE_DISABLE;
    advConfig.burst_size = 32;

    MXC_DMA_ConfigChannel(config, firstTransfer);
    MXC_DMA_AdvConfigChannel(advConfig);

    mxc_dma_srcdst_t secondTransfer;
    secondTransfer.ch = g_dma_ch;
    secondTransfer.source = srcdata2;
    secondTransfer.dest = dstdata2;
    secondTransfer.len = MAX_SIZE;

    MXC_DMA_SetSrcDst(firstTransfer);

    retval = MXC_DMA_SetSrcReload(secondTransfer);
    if (retval != E_NO_ERROR) {
        printf("Failed MXC_DMA_SetReload.\n");
        return retval;
    }
    
    MXC_DMA_SetCallback(g_dma_ch, my_int_func);
    MXC_DMA_EnableInt(g_dma_ch);
    MXC_DMA_Start(g_dma_ch);
    
    // Validate
    if (memcmp(srcdata, dstdata, MAX_SIZE) != 0 || 
            memcmp(srcdata2, dstdata2, MAX_SIZE) != 0) {
        printf("Data mismatch.\n");
        retval = -1;
    } else {
        printf("Data verified.\n");
    }

    if (MXC_DMA_ReleaseChannel(g_dma_ch) != E_NO_ERROR) {
        printf("Failed to release channel %d\n", g_dma_ch);
    }
    
    return retval;
}

/******************************* Public Functions ****************************/
int test_dma(void)
{
    int retval;
    
    // Wait 5 sec to pc side prepared
    wait_us(5*1000*1000); 
    
    printf("\n\n***** DMA Example *****\n");
    
    NVIC_SetVector(DMA0_IRQn, (uint32_t)DMAx_IRQHandler);
    NVIC_EnableIRQ(DMA0_IRQn);

    MXC_DMA_Init();
    
    /* DMA memory to memory example*/
    retval = dma_example_mem2mem();
    printf("DMA mem2mem example %s\n", (retval == 0) ? "succeeded": "failed");
    
    /* DMA memory to memory example with reload feature*/
    retval = dma_example_mem2mem_with_reload();
    printf("DMA mem2mem reload example %s\n", (retval == 0) ? "succeeded": "failed");
    
    while(1) {
        ;
    }
    
    return 0;
}
