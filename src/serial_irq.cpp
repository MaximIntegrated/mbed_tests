

#include "mxc_tests.h"

#if  TEST_SERIAL_IRQ
#include "mbed.h"


// Create a DigitalOutput object to toggle an LED whenever data is received.
static DigitalOut led(LED1);

// Create a UnbufferedSerial object with a default baud rate.
#if defined(TARGET_MAX32660) 
    static UnbufferedSerial  serial_port(UART0_TX, UART0_RX, 115200);
    static UnbufferedSerial  debug_port(UART1A_TX, UART1A_RX, 115200);
#elif defined(TARGET_MAX32670) 
    static UnbufferedSerial  serial_port(UART1_TX, UART1_RX, 115200);
    static UnbufferedSerial  debug_port(UART0_TX, UART0_RX, 115200);
#endif

static char g_buf[512];
static int  g_rxLen;

static void on_rx_interrupt(void)
{
    // Toggle the LED.
    //led = !led;

    // Read the data to clear the receive interrupt.
    g_rxLen = serial_port.read(g_buf, sizeof(g_buf));
    if (g_rxLen > 0) {
        // send over debug port
        debug_port.write(g_buf, g_rxLen);
    }
}

int test_serial_irq(void)
{
    // Set desired properties (115200-8-N-1).
    serial_port.baud(115200);
    serial_port.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );

    // Register a callback to process a Rx (receive) interrupt.
    serial_port.attach(&on_rx_interrupt, SerialBase::RxIrq);

    while(1) {
        ;
    }
}
#endif // TEST_SERIAL_IRQ
