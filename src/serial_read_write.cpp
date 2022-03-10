

#include "mxc_tests.h"

#if  TEST_SERIAL_READ_WRITE
#include "mbed.h"

#if defined(TARGET_MAX32660) 
    static UnbufferedSerial  pc(UART0_TX, UART0_RX, 9600);
#elif defined(TARGET_MAX32670) 
    static UnbufferedSerial  pc(UART1_TX, UART1_RX, 9600);
#endif

int test_serial_read_write(void) 
{
    char buf[64];

    DigitalOut led(LED1);

    pc.baud(9600);
    pc.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );
    
	sprintf(buf, "\n\rThis is Mbed Uart Test!!!\n\r");
    pc.write(buf, strlen(buf));
	while(1){
		if(pc.readable()){
            char c;
            pc.read(&c, 1);
			pc.write(&c, 1);
            
            led = !led;
            printf("%c", c);
            fflush(stdout);
		}
	}
}
#endif // TEST_SERIAL_READ_WRITE
