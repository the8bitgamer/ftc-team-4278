#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)
#pragma config(Sensor, S2, HTSMUX, sensorLowSpeed)

#include "drivers/HTGYRO-driver.h"

void move90Degrees()
{
	float gyroValue = 0;
	float summationValue = 0;
	while(summationValue < 90)
	{
		motor[motorsLeft] = 20;
		motor[motorsRight] = -20;
		gyroValue = HTGYROreadRot(HTSMUX);
		summationValue += gyroValue/250;
		wait1Msec(4);
	}
}

task main()
{
//	HTSMUXinit();
//	HTSMUXscanPorts(HTSMUX);
	HTGYROstartCal(HTSMUX);
  //HTGYROstartCal(HTGyro);
	float sfvmaiv = HTGYROreadRot(HTSMUX);
	move90Degrees();
}
