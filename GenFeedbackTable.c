#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,  none,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     sensorSlideEndstop, sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     mRight2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     mRight1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     mLeft1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mLeft2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mSlide1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     mSlide2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     mChain,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_3,    tubeHook1,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    tubeHook2,            tServoStandard)

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

	servo[tubeHook1] = 128;
	servo[tubeHook2] = 128;



	writeDebugStreamLine("int powerToSpeedTable[101] = {");

	int newlineCounter = 0;

	nMotorEncoder[mLeft1] = 0;

 	for(int counter = 0; counter <= 100; ++counter)
 	{
 		if(newlineCounter++ >= 10)
 		{
 			writeDebugStreamLine(" ");
 			newlineCounter = 1;
 		}

 		motor[mLeft1] = counter;
 		motor[mLeft2] = counter;
 		nMotorEncoder[mLeft1] = 0;

 		Sleep(1000);

 		//in degrees per millisecond
 		//though, there's not 360 degrees in a revolution
 		int angularSpeed = leftEncoder;

 		writeDebugStream("	%d,", angularSpeed);
	}

	writeDebugStreamLine("};");
}
