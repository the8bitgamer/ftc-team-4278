#pragma config(Hubs,   S1,  HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,   S2,  HTServo,  none,     none,     none)
#pragma config(Hubs,   S4,  HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,         ,  sensorI2CMuxController)
#pragma config(Sensor, S2,         ,  sensorI2CMuxController)
#pragma config(Sensor, S3, sensorIR,  sensorI2CCustom)
#pragma config(Sensor, S4,    HTSPB,  sensorI2CMuxController)
#pragma config(Motor,   mtr_S1_C1_1,   mArm2, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,   mtr_S1_C1_2,   mArm1, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,   mtr_S1_C2_1, mRight1, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,   mtr_S1_C2_2, mRight2, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,   mtr_S4_C1_1,  mLeft1, tmotorTetrix, openLoop)
#pragma config(Motor,   mtr_S4_C1_2,  mLeft2, tmotorTetrix, openLoop)
#pragma config(Motor,   mtr_S4_C2_1,   mSpin, tmotorTetrix, openLoop)
#pragma config(Motor,   mtr_S4_C2_2,  mNull1, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1, servoL2, tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2, servoL1, tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,  servo3, tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,  servo4, tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,  servo5, tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,  servo6, tServoNone)
//*!!Codez automagically venerated by 'ROWBOT SEA' conflagration lizard               !!*//

#include "drivers/autoutils.h"

task main() {
	float low = 0;
	float high = 2;
	float mid = 1;
	while(true) {
		mid = (low + high) / 2.0;
		nxtDisplayTextLine(3, "%f", high);
		nxtDisplayTextLine(4, "%f", mid);
		nxtDisplayTextLine(5, "%f", low);

		clearEncoders();
		setLeftMotors(50.0*mid);
		setRightMotors(50);
		wait1Msec(3000);
		setLeftMotors(0); setRightMotors(0);

		bool cont = false;
		while(!cont) {
			if(nNxtButtonPressed == BTN_RIGHT) {high = mid; cont = true;}
			if(nNxtButtonPressed == BTN_LEFT) {low = mid; cont = true;}
		}
	}
}
