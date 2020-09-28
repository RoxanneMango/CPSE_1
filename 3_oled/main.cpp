//#include "i2c_scanner.h"

#include <Wire.h>
#include <RTCDue.h>

#include "draw.h"

// Due	20 (SDA), 21 (SCL), SDA1, SCL1

int
main( void )
{	
	watchdogSetup();
	init();
	delay(1);
	
	RingBuffer rx_buffer;
	RingBuffer tx_buffer;
	UARTClass uart(UART, UART_IRQn, ID_UART, &rx_buffer, &tx_buffer);
	//
	uart.begin(9600);
	
	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	display.clearDisplay();

	//i2c_scanner();

	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
		printf("SSD1306 allocation failed\n\r");
		for(;;); // Don't proceed, loop forever
	}

	RTCDue rtc(RC); //	RTCDue rtc(XTAL);

	uint8_t seconds = 20;
	uint8_t minutes = 30;
	uint8_t hours = 11;
	//
	const uint8_t day = 12;
	const uint8_t month = 2;
	const uint16_t year = 2016;

	rtc.begin();
	// Set the time
	rtc.setHours(hours);
	rtc.setMinutes(minutes);
	rtc.setSeconds(seconds);
	// Set the date
	rtc.setDay(day);
	rtc.setMonth(month);
	rtc.setYear(year);

	constexpr LookupTable_time<24,18,12> lookup_table_h;
	constexpr LookupTable_time<60,24,60> lookup_table_m;
	constexpr LookupTable_time<60,24,60> lookup_table_s;
	//
	constexpr LookupTable_clock_face<12> clock_face;

	display.clearDisplay();
	draw_clock_face(display, clock_face);
	display.display();

	for (;;)
	{
		
		if (rtc.getSeconds() != seconds)
		{
			draw_second(display, seconds, 0, lookup_table_s);
			draw_minute(display, minutes,0, lookup_table_m);
			draw_hour(display, hours,0, lookup_table_h);
			draw_second(display, rtc.getSeconds(), 1, lookup_table_s);
			draw_minute(display, rtc.getMinutes(), 1, lookup_table_m);
			draw_hour(display, rtc.getHours(),1, lookup_table_h);
			display.display(); 
			seconds=rtc.getSeconds();
			minutes=rtc.getMinutes();
			hours=rtc.getHours();
			redraw_clock_face_elements(display);
		}
		
	}
	return 0;
}

	// Wire definition:
	// TwoWire Wire = TwoWire(WIRE_INTERFACE, Wire_Init, Wire_Deinit);
	// arduino/hardware/sam/1.6.12/libraries/Wire/src/Wire.cpp

	// WIRE_INTERFACE definition:
	// arduino/hardware/sam/1.6.12/variants/arduino_due_x/variant.h
	// #define PIN_WIRE_SDA         (20u)
	// #define PIN_WIRE_SCL         (21u)
	// #define WIRE_INTERFACE       TWI1
	// #define WIRE_INTERFACE_ID    ID_TWI1
	// #define WIRE_ISR_HANDLER     TWI1_Handler
	// #define WIRE_ISR_ID          TWI1_IRQn
	
	// WIRE_INTERFACE definition definitions:
	// arduino/hardware/sam/1.6.12/system/CMSIS/Device/ATMEL/sam3xa/include/sam3x8e.h
	// TWI1_IRQn            = 23, /**< 23 SAM3X8E Two-Wire Interface 1 (TWI1) */
	// void TWI1_Handler       ( void );
	// #define ID_TWI1   (23) /**< \brief Two-Wire Interface 1 (TWI1) */
	// #define TWI1       (0x40090000U) /**< \brief (TWI1      ) Base Address */
