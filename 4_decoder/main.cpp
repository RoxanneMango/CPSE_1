// Header file(s) for watchdogSetup(), init(), delay(), and RingBuffer & UARTClass objects
#include <Arduino.h>

#include "compressor.hpp"

extern "C" void decode();

int
main( void )
{
	watchdogSetup();
	init();
	delay(1);

	RingBuffer rx_buffer;
	RingBuffer tx_buffer;
	UARTClass uart(UART, UART_IRQn, ID_UART, &rx_buffer, &tx_buffer);

	uart.begin(9600);

	char * array = "Hello world aa aa aa bb bb bb cc cc cc cc abbaabababbbaa";
	char * array_ptr = array;
	//
	char buffer[4096] = {0};
	char * buffer_ptr = buffer;

	lz_compressor< 4096 > compressor;
	compressor.compress( 
		[ &array_ptr ]()-> int { return *(array_ptr++); },
		[ &buffer_ptr ]( char c ) { *(buffer_ptr++) = c; }
	);

	buffer_ptr = buffer;
	
	printf("array:\t\t%s\r\n", array);
	printf("compressed:\t%s\r\n", buffer_ptr);
	printf("decompressed:\t");
	
	decode();

	for (;;)
	{
		delay(5000);
	}
	return 0;
}