#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)

#include "JoystickDriver.c"

#define leftPower 100
#define rightPower 50

task main()
{
	nMotorEncoder[motorsLeft] = 0;
	nMotorEncoder[motorsRight] = 0;
	
	motor[motorsLeft] = leftPower;
	motor[motorsRight] = rightPower;
	
	while(!joy1Btn(1)) {getJoystickSettings(joystick);}
	
	while(true)
	{
		nxtDisplayTextLine(2, "Left: %d", nMotorEncoder[motorsLeft]);
		nxtDisplayTextLine(3, "Right: %d", nMotorEncoder[motorsRight]);
	}
}