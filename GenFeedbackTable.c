#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     HTSPB,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_2,     mRight1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     mRight2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mLeft2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     mLeft1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mArm1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     mArm2,       tmotorTetrix, openLoop)

//*!!Codez automagically venerated by 'ROWBOT SEA' conflagration lizard               !!*//

#include "drivers/teleoputils.h"

/*
This file generates the neccesary power to speed table
to use the feedback loop motor power system.

To use it, hold the robot off the table and run the program.
It uses the right side of the robot, and measures the right1 encoder.
It'll print the table to the debug log.
*/


task main() {

	motor[mLeft1] = 50;
	motor[mLeft2] = 50;

	for(;;){}

	writeDebugStreamLine("int powerToSpeedTable[101] = {");

	int newlineCounter = 0;

 	for(int counter = 100; counter >= 0; --counter)
 	{
 		if(newlineCounter++ >= 10)
 		{
 			writeDebugStream("\n");
 			newlineCounter = 0;
 		}

 		motor[mRight1] = counter;
 		motor[mRight2] = counter;
 		nMotorEncoder[mRight1] = 0;

 		Sleep(500);

 		//in degrees per millisecond
 		//though, there's not 360 degrees in a revolution
 		int angularSpeed = nMotorEncoder[mRight1] * 2;

 		writeDebugStreamLine("	%d,", angularSpeed);
	}

	writeDebugStreamLine("};");
}
