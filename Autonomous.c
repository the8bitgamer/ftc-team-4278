#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ultrasonic,     sensorSONAR)
#pragma config(Motor,  mtr_S1_C2_1,     mRight2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mRight1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     mLeft1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     mLeft2,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_3,    tubeHook1,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    tubeHook2,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "AutoPrograms.h"

#define WAIT_FOR_START

int AUTO_PROGRAM = 0;

void optionScreen() {
	nxtDisplayTextLine(0, "NXT:  %.2f V", ((float)nAvgBatteryLevel)/1000.0);
	if(externalBatteryAvg > 0) nxtDisplayTextLine(1, "EXT: %.2f V", ((float)externalBatteryAvg)/1000.0);
		else nxtDisplayTextLine(1, "EXT: OFF");

	if(nAvgBatteryLevel < NXT_LOW_BAT) nxtDisplayTextLine(2, "***NXT     LOW***");
	if(externalBatteryAvg < EXT_LOW_BAT) nxtDisplayTextLine(2, "***    EXT LOW***");
	if(nAvgBatteryLevel < NXT_LOW_BAT && externalBatteryAvg < EXT_LOW_BAT) nxtDisplayTextLine(2, "***NXT EXT LOW***");

	while(nNxtButtonPressed != BTN_CENTER) {
		if(AUTO_PROGRAM == 0)
		{
		   nxtDisplayBigTextLine(4, "Knock");
		   nxtDisplayBigTextLine(6, "Balls");
		}
		else if(AUTO_PROGRAM == 1)
		{
			nxtDisplayBigTextLine(4, "DriveOff");
			nxtDisplayBigTextLine(6, "Ramp");
		}
		else if(AUTO_PROGRAM == 2)
		{
			nxtDisplayBigTextLine(4, "Drag");
			nxtDisplayBigTextLine(6, "Goal");
		}
		else if(AUTO_PROGRAM == 3)
		{
			nxtDisplayBigTextLine(4, "BallsW/");
			nxtDisplayBigTextLine(6, "Delay");
		}

		if(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) {
			PlaySound(soundShortBlip);
			if(nNxtButtonPressed == BTN_LEFT) AUTO_PROGRAM--;
			if(nNxtButtonPressed == BTN_RIGHT) AUTO_PROGRAM ++;
			if(AUTO_PROGRAM > 3) AUTO_PROGRAM = 0;
			if(AUTO_PROGRAM < 0) AUTO_PROGRAM = 3;

			while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
		}
	} PlaySound(soundBlip); while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);
	nxtDisplayTextLine(7, "*** LOCKED ***");

#ifdef WAIT_FOR_START
	waitForStart();
#endif

	switch(AUTO_PROGRAM)
	{
	case 0:
		knockDownBalls();
		break;
	case 1:
		driveOffRamp();
		break;
	case 2:
		dragGoal();
		break;
	case 3:
		knockDownBallsWithDelay();
	}

}

task main() {
	//--------------------------------------------------------
	//Setup stuff goes here
	//--------------------------------------------------------

	//StartTask(monitorFeedback);
	retractHooks();

	//--------------------------------------------------------
	//Main sequence goes here
	//--------------------------------------------------------
	optionScreen();

}
