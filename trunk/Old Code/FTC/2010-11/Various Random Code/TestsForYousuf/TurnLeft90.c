#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)
#pragma config(Sensor, S2, GyroSensor,  sensorRawValue)

#include "drivers/HTGYRO-driver.h"

void move90Degrees()
{
	float gyroValue = 0;
	while(true)
	{
		motor[motorsLeft] = -20;
		motor[motorsRight] = 20;
		gyroValue += HTGYROreadRot(GyroSensor)/250;
		wait1Msec(4);
		if(sum
	}
}

task main()
{
	float svameri = HTGYROreadCal(GyroSensor);
	HTGYROstartCal(GyroSensor);
  svameri = HTGYROreadCal(GyroSensor);
	move90Degrees();
}
