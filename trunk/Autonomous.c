#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     mRight1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mRight2,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     mArm2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mSpin,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mLeft1,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     mLeft2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     mArm1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servoL1,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servoL2,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automagically venerated by 'ROBOTC' configuration lizard               !!*//

#include "drivers/autoutils.h"
#include "drivers/hitechnic-irseeker-v2.h"

void rbtMoveFd(float inches) {
	int enc = getEncoderByInches(inches);
	clearEncoders();
	int norm = -1.0*sgn(inches);

	while(leftEncoder < enc || rightEncoder < enc) {
		dt = (float)time1[T1]; ClearTimer(T1);
		nxtDisplayTextLine(0, "E%i", enc);
		nxtDisplayTextLine(1, "L%i", leftEncoder);
		nxtDisplayTextLine(2, "R%i", rightEncoder);
		float avgEnc = ((float)(leftEncoder+rightEncoder))/2.0;
		float tVel = (enc - avgEnc > 3000 ? 500 : 500*(((float)(enc-avgEnc))/3000.0));
		float lVel = ((float)(leftEncoder-lastLEnc))/dt;
		float rVel = ((float)(rightEncoder-lastREnc))/dt;
		lastLEnc = leftEncoder; lastREnc = rightEncoder;

		float pLEVel = lVel-tVel;
		float pREVel = rVel-tVel;
		float dLEVel = ((float)(pLEVel - lastLEVel))/dt;
		float dREVel = ((float)(pREVel - lastREVel))/dt;
		iLEVel += dt*((float)pLEVel);
		iREVel += dt*((float)pREVel);

		float lPow = norm*kPL*pLEVel; float rPow = norm*kPR*pREVel;
		lPow -= kDL*dLEVel; rPow -= kDR*dREVel;
		lPow += kIL*iLEVel; rPow += kIR*iLEVel;

		setLeftMotors (lPow);
		setRightMotors(rPow);

		nxtDisplayTextLine(3, "PLe:%i", pREVel);
		nxtDisplayTextLine(4, "PRe:%i", pREVel);
		nxtDisplayTextLine(5, "DLe:%f", dLEVel);
		nxtDisplayTextLine(6, "DRe:%f", dREVel);
		nxtDisplayTextLine(7, "ILe:%f", iLEVel);
		nxtDisplayTextLine(8, "ILe:%f", iREVel);

		wait1Msec(50);
	}
	setLeftMotors(0); setRightMotors(0);
}

void rbtArcRight(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*55);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0);
}

void rbtArcLeft(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setRightMotors(sgn(degs)*55);
	while(rightEncoder < enc) wait1Msec(10);
	setRightMotors(0);
}

void rbtTurnRight(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*55);
	setRightMotors(-1*sgn(degs)*55);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

void rbtTurnLeft(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(-1*sgn(degs)*55);
	setRightMotors(sgn(degs)*55);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

task main() {
	displayDiagnostics();
initialize:
	unlockArmMotors();
	rbtMoveFd(48);
	//IR detection and selection
crateOne:
	//Move and score at crate 1
crateTwo:
	//Move and score at crate 2
crateThree:
	//Move and score at crate 3
crateFour:
	//Move and score at crate 4
leftBridge:
	//Move to the left bridge
rightBridge:
	//Move to the right bridge
leftError:
	//Move on error from the left bridge
rightError:
	//Move on error from the right bridge
normstop:
	while(true) wait1Msec(100);
estop:
	StopAllTasks();
}
