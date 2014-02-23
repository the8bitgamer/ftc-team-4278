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

#include "drivers/sharedutils.h"

void motorStep(tMotor m) {
	motor[m] = 100;
	wait1Msec(500);
	motor[m] = -100;
	wait1Msec(500);
	motor[m] = 0;
	while(nNxtButtonPressed != 3);
}

task main() {
	nxtDisplayTextLine(3, "mRight1"); motorStep(mRight1);
	nxtDisplayTextLine(3, "mRight2"); motorStep(mRight2);
	nxtDisplayTextLine(3, "mLeft1");  motorStep(mLeft1);
	nxtDisplayTextLine(3, "mLeft2");  motorStep(mLeft2);
	nxtDisplayTextLine(3, "mSpin");   motorStep(mSpin);
	nxtDisplayTextLine(3, "mArm1");   motorStep(mArm1);
	nxtDisplayTextLine(3, "mArm2");   motorStep(mArm2);

	nxtDisplayTextLine(3, "Servos");
	lockArmMotors();
	wait1Msec(250);
	unlockArmMotors();
}
