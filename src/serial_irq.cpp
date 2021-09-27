

#include "mbed.h"


// Create a DigitalOutput object to toggle an LED whenever data is received.
static DigitalOut led(LED1);

// Create a UnbufferedSerial object with a default baud rate.
static UnbufferedSerial  serial_port(UART0_TX, UART0_RX, 9600);

static void on_rx_interrupt(void)
{
    char c;

    // Toggle the LED.
    led = !led;

    // Read the data to clear the receive interrupt.
    if (serial_port.read(&c, 1)) {
        // Echo the input back to the terminal.
        serial_port.write(&c, 1);
    }
}

int test_serial_irq(void)
{
    // Set desired properties (9600-8-N-1).
    serial_port.baud(9600);
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
