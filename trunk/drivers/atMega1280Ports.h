#if !defined(__atMega1280Ports__H_)
#define __atMega1280Ports__H_


#include <RobotFirmware/Includes/atMega328ports.h>

typedef enum TAtMega1280SensorPorts
{
	atMega1280_Analog0 = 0,	// PF0
	atMega1280_Analog1,			// PF1
	atMega1280_Analog2,			// PF2
	atMega1280_Analog3,			// PF3
	atMega1280_Analog4,			// PF4
	atMega1280_Analog5,			// PF5
	atMega1280_Analog6 = 6,	// PF6
	atMega1280_Analog7,			// PF7

	atMega1280_Analog8,			// PK0
	atMega1280_Analog9,			// PK1
	atMega1280_Analog10,		// PK2
	atMega1280_Analog11,		// PK3
	atMega1280_Analog12,		// PK4
	atMega1280_Analog13,		// PK5
	atMega1280_Analog14,		// PK6
	atMega1280_Analog15,		// PK7

	atMega1280_Digital0 = 16,//PE0 - RXD0
	atMega1280_Digital1,		// PE1 - TXD0
	atMega1280_Digital2,		// PE4 - OC3B (PWM)
	atMega1280_Digital3,		// PE5 - OC3C (PWM)
	atMega1280_Digital4,		// PG5 - OC0B (PWM)
	atMega1280_Digital5,		// PE3 - OC3A (PWM)
	atMega1280_Digital6,		// PH3 - OC4A (PWM)
	atMega1280_Digital7,		// PH4 - OC4B (PWM)
	atMega1280_Digital8,		// PH5 - OC4C (PWM)
	atMega1280_Digital9,		// PH6 - OC2B (PWM)

	atMega1280_Digital10,		// PB4 - OC2A (PWM)
	atMega1280_Digital11,		// PB5 - OC1A (PWM)
	atMega1280_Digital12,		// PB6 - OC1B (PWM)
	atMega1280_Digital13,		// PB7 - OC0A / OC1C (PWM)
	atMega1280_Digital14,		// PJ1 - TXD3
	atMega1280_Digital15,		// PJ0 - RXD3
	atMega1280_Digital16,		// PH1 - TXD2
	atMega1280_Digital17,		// PH0 - RXD2
	atMega1280_Digital18,		// PD3 - TXD1
	atMega1280_Digital19,		// PD2 - RXD1

	atMega1280_Digital20,		// PD1 - SDA
	atMega1280_Digital21,		// PD0 - SCL
	atMega1280_Digital22,		// PA0
	atMega1280_Digital23,		// PA1
	atMega1280_Digital24,		// PA2
	atMega1280_Digital25,		// PA3
	atMega1280_Digital26,		// PA4
	atMega1280_Digital27,		// PA5
	atMega1280_Digital28,		// PA6
	atMega1280_Digital29,		// PA7


	atMega1280_Digital30,		// PC7
	atMega1280_Digital31,		// PC6
	atMega1280_Digital32,		// PC5
	atMega1280_Digital33,		// PC4
	atMega1280_Digital34,		// PC3
	atMega1280_Digital35,		// PC2
	atMega1280_Digital36,		// PC1
	atMega1280_Digital37,		// PC0
	atMega1280_Digital38,		// PD7
	atMega1280_Digital39,		// PG2

	atMega1280_Digital40,		// PG1
	atMega1280_Digital41,		// PG0
	atMega1280_Digital42,		// PL7
	atMega1280_Digital43,		// PL6
	atMega1280_Digital44,		// PL5 - OC5C (PWM)
	atMega1280_Digital45,		// PL4 - OC5B (PWM)
	atMega1280_Digital46,		// PL3 - OC5A (PWM)
	atMega1280_Digital47,		// PL2
	atMega1280_Digital48,		// PL1
	atMega1280_Digital49,		// PL0

	atMega1280_Digital50,		// PB3
	atMega1280_Digital51,		// PB2
	atMega1280_Digital52,		// PB1
	atMega1280_Digital53,		// PB0

	
	//
	// ROboCub Port Names
	//
	
	//atMega1280_internalButton_0,																// PD2	Port D,  Pin 2	 Left
	atMega1280_internalButton_1,																	// PD3	Port D,  Pin 3	 Center
	//atMega1280_internalButton_2,																// PD4	Port D,  Pin 4	 Right
	//atMega1280_internalButton_3,																// PD5	Port D,  Pin 5	 Exit
	//atMega1280_internalButton_4,																// PD6	Port D,  Pin 6  Exit 2

	//	Following are for internal use
	
	atMega1280_Speaker,																						// PE3	Port E,  Pin 3  OC3A

	atMega1280_SoftPWMMotor_0_Dir,																// PA0 & PA1	Robocub Only
	atMega1280_SoftPWMMotor_1_Dir,																// PA2 & PA3	Robocub Only
	atMega1280_SoftPWMMotor_2_Dir,																// PA4 & PA5	Robocub Only
	atMega1280_SoftPWMMotor_3_Dir,																// PA6 & PA7	Robocub Only

	atMega1280_SoftPWMMotor_0_Enable,															// PE2	Robocub Only
	atMega1280_SoftPWMMotor_1_Enable	= atMega1280_Digital5,			// PE3	Port E,  Pin 3   ---- same as atMega1280_Speaker
	atMega1280_SoftPWMMotor_2_Enable	= atMega1280_Digital2,			// PE4	Port E,  Pin 4	
	atMega1280_SoftPWMMotor_3_Enable	= atMega1280_Digital3,			// PE5	Port E,  Pin 5

	atMega1280_LCD_Backlight					= atMega1280_Digital12,			// PB6	Port B,  Pin 6

	atMega1280_S0_Analog_A						= arduino_Analog0,
	atMega1280_S0_Analog_B						= arduino_Analog1, 
	atMega1280_S1_Analog_A						= arduino_Analog2,
	atMega1280_BatteryMonitor					= arduino_Analog3,

	atMega1280_S2_Analog_A						= arduino_Analog4,
	atMega1280_S2_Analog_B						= arduino_Analog5,
	atMega1280_S3_Analog_A						= atMega1280_Analog6,
	atMega1280_S3_Analog_B						= atMega1280_Analog7,

	atMega1280_S0_Digital							= atMega1280_Digital33,			// PC4	Port C,  Pin 4
	atMega1280_S1_Digital							= atMega1280_Digital32,			// PC5	Port C,  Pin 5
	atMega1280_S2_Digital							= atMega1280_Digital31,			// PC6	Port C,  Pin 6
	atMega1280_S3_Digital							= atMega1280_Digital30,			// PC7	Port C,  Pin 7


	atMega1280_SPI_SCE								= atMega1280_Digital53,		// PB0  Port B,  Pin 0 - Used for internal SPI
	atMega1280_SPI_SCK								= atMega1280_Digital52,		// PB1  Port B,  Pin 1 - Used for internal SPI
	atMega1280_SPI_MOSI								= atMega1280_Digital51,		// PB0  Port B,  Pin 2 - Used for internal SPI
	atMega1280_SPI_RST								= atMega1280_Digital10,		// PB4  Port B,  Pin 4 - Used for internal SPI
	atMega1280_SPI_DorC								= atMega1280_Digital11,		// PB5  Port B,  Pin 5 - Used for internal SPI

	atMega1280_UART_RX_0							= atMega1280_Digital0,		// PE0	Port E,  Pin 0
	atMega1280_UART_TX_0							= atMega1280_Digital1,		// PE1	Port E,  Pin 1
	atMega1280_UART_RX_1							= atMega1280_Digital18,		// PD2	Port D,  Pin 2
	atMega1280_UART_TX_1							= atMega1280_Digital28,		// PD3	Port D,  Pin 3

} TAtMega1280SensorPorts;  


#endif
