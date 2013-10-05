#if !defined(__atMega128Ports__H_)
#define __atMega128Ports__H_

//
// Temporary Kludge for RoboCub
//

typedef enum TAtMega128SensorPorts 
{

	atMega128_S0_Analog_A			= 0,	// Port F,  Pin 0
	atMega128_S0_Analog_B,					// Port F,  Pin 1 
	atMega128_S1_Analog_A,					// Port F,  Pin 2
	atMega128_BatteryMonitor,				// Port F,  Pin 3			//Battery monitor

	atMega128_S2_Analog_A,					// Port F,  Pin 4
	atMega128_S2_Analog_B,					// Port F,  Pin 5 
	atMega128_S3_Analog_A,					// Port F,  Pin 6
	atMega128_S3_Analog_B,					// Port F,  Pin 7 

	atMega128_S0_Digital,						// Port C,  Pin 4
	atMega128_S1_Digital,						// Port C,  Pin 5
	atMega128_S2_Digital,						// Port C,  Pin 6
	atMega128_S3_Digital,						// Port C,  Pin 7

	atMega128_StatusLED_0,					// Port E,  Pin 2
	atMega128_StatusLED_1,					// Port E,  Pin 3
	atMega128_LCD_Backlight,				// Port B,  Pin 6
	
	atMega128_internalButton_0,			// Port D,  Pin 2	 Left
	atMega128_internalButton_1,			// Port D,  Pin 3	 Center
	atMega128_internalButton_2,			// Port D,  Pin 4	 Right
	atMega128_internalButton_3,			// Port D,  Pin 5	 Exit
	atMega128_internalButton_4,			// Port D,  Pin 6  Exit 2

	//	Following are for internal use
	
	atMega128_Speaker,							// Port E,  Pin 3  OC3A

	atMega128_SoftPWMMotor_0_Dir,					// PA0 PA1 Port A,  Pin 0 & 1
	atMega128_SoftPWMMotor_1_Dir,					// PA2 PA3 Port A,  Pin 2 & 3
	atMega128_SoftPWMMotor_2_Dir,					// PA4 PA5 Port A,  Pin 4 & 5
	atMega128_SoftPWMMotor_3_Dir,					// PA6 PA7 Port A,  Pin 6 & 7

	atMega128_SoftPWMMotor_0_Enable,			// PE2 Port E,  Pin 2
	atMega128_SoftPWMMotor_1_Enable,			// PE3 Port E,  Pin 3
	atMega128_SoftPWMMotor_2_Enable,			// PE4 Port E,  Pin 4
	atMega128_SoftPWMMotor_3_Enable,			// PE5 Port E,  Pin 5

	atMega128_SPI_SCE,							// Port B,  Pin 0 - Used for internal SPI
	atMega128_SPI_SCK,							// Port B,  Pin 1 - Used for internal SPI
	atMega128_SPI_MOSI,							// Port B,  Pin 2 - Used for internal SPI
	atMega128_SPI_RST,							// Port B,  Pin 4 - Used for internal SPI
	atMega128_SPI_DorC,							// Port B,  Pin 5 - Used for internal SPI

	atMega128_UART_RX_0,						// Port E,  Pin 0
	atMega128_UART_TX_0,						// Port E,  Pin 1
	atMega128_UART_RX_1,						// Port D,  Pin 2
	atMega128_UART_TX_1,						// Port D,  Pin 3

} TAtMega128SensorPorts;  


#endif
