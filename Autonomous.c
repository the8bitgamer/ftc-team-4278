#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     mLeft1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mRight1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     mShift1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mShift2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mLeft2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     mLeft3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     mRight2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     mRight3,       tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    sShifter,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    sLock,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Codez automagically venerated by 'ROWBOT SEA' conflagration lizard               !!*//

#include "autoconst.h"
#include "drivers/autoutils.h"
//#include "drivers/autodummy.h"

int OPT_SIDE = 0; int OPT_AUTO = 0; int OPT_DELAY = 0; int OPT_BRIDGE = 0;

void initializeRobot() {unlockArmMotors();}
void moveToBridge() {
	setLeftMotors(60*LEFT_POW_DIFF);
	setRightMotors(60*RIGHT_POW_DIFF);
	wait1Msec(3000);
	setLeftMotors(0);
	setRightMotors(0);
}

void runAutoLeft() {
	int irEncDist = -1;
	     if(OPT_AUTO == 0) {irEncDist = rbtMoveToIR(C4_ENC, 6000) - getEncoderByInches(IR_REALIGN); rbtMoveFdEnc(IR_REALIGN, 2000);}
	else if(OPT_AUTO == 1) {rbtMoveFdEnc(C1_ENC, 5000); irEncDist = C1_ENC;}
	else if(OPT_AUTO == 2) {rbtMoveFdEnc(C2_ENC, 5000); irEncDist = C2_ENC;}
	else if(OPT_AUTO == 3) {rbtMoveFdEnc(C3_ENC, 5000); irEncDist = C3_ENC;}
	else if(OPT_AUTO == 4) {rbtMoveFdEnc(C4_ENC, 5000); irEncDist = C4_ENC;}

	rbtArcRight(90);         //Turn to crate
	rbtMoveFdDist(4, 3000); //Against crate
	dumpArm();               //Dump blocks
	rbtMoveFdDist(-1, 1000);  //Back away

	if(OPT_BRIDGE == 0) OPT_BRIDGE = C23_THRESH < irEncDist ? 2 : 1;
	if(OPT_BRIDGE == 1) { //Left
		rbtArcLeft(90);
		rbtMoveFdEnc(irEncDist+getEncoderByInches(WHEELBASE+1), 6000);
		rbtArcLeft(-90);
		rbtMoveFdDist(18, 3000);
		rbtArcLeft(-90);
		rbtMoveFdDist(30, 4000);
	}
	if(OPT_BRIDGE == 2) { //Right
		rbtArcRight(-90);
		rbtMoveFdEnc(BRIDGE_ENC-irEncDist+getEncoderByInches(1), 6000);
		rbtArcRight(90);
		rbtMoveFdDist(18, 3000);
		rbtArcRight(90);
		rbtMoveFdDist(30, 4000);
	}
	if(OPT_BRIDGE == 3) //Back off
		rbtMoveFdDist(-24, 6000);
	//if(OPT_BRIDGE == 4); //None
}

void runAutoRight() {
	int irEncDist = -1;
	     if(OPT_AUTO == 0) {irEncDist = rbtMoveToIR(C4_ENC, 6000) - getEncoderByInches(IR_REALIGN); pause(); rbtMoveFdDist(-IR_REALIGN, 2000);}
	else if(OPT_AUTO == 1) {rbtMoveFdEnc(C1_ENC, 5000); irEncDist = C1_ENC;}
	else if(OPT_AUTO == 2) {rbtMoveFdEnc(C2_ENC, 5000); irEncDist = C2_ENC;}
	else if(OPT_AUTO == 3) {rbtMoveFdEnc(C3_ENC, 5000); irEncDist = C3_ENC;}
	else if(OPT_AUTO == 4) {rbtMoveFdEnc(C4_ENC, 5000); irEncDist = C4_ENC;}

	rbtArcLeft(-90);
	rbtMoveFdDist(4, 3000);
	dumpArm();
	rbtMoveFdDist(-1, 1000);

	if(OPT_BRIDGE == 0) OPT_BRIDGE = C23_THRESH < irEncDist ? 1 : 2;
	if(OPT_BRIDGE == 1) { //Left
		rbtArcLeft(90);
		rbtMoveFdEnc(BRIDGE_ENC-irEncDist+getEncoderByInches(1), 6000);
		rbtArcLeft(-88);
		rbtMoveFdDist(18, 3000);
		rbtArcLeft(-92);
		rbtMoveFdDist(30, 4000);
	}
	if(OPT_BRIDGE == 2) { //Right
		rbtArcRight(-90);
		rbtMoveFdEnc(irEncDist+getEncoderByInches(WHEELBASE+1), 6000);
		rbtArcRight(88);
		rbtMoveFdDist(18, 3000);
		rbtArcRight(92);
		rbtMoveFdDist(30, 4000);
	}
	if(OPT_BRIDGE == 3) //Back off
		rbtMoveFdDist(-24, 6000);
	//if(OPT_BRIDGE == 4); //None
}

void optionScreen() {
	nxtDisplayTextLine(0, "NXT:  %.2f V", ((float)nAvgBatteryLevel)/1000.0);
	if(externalBatteryAvg > 0) nxtDisplayTextLine(1, "EXT: %.2f V", ((float)externalBatteryAvg)/1000.0);
		else nxtDisplayTextLine(1, "EXT: OFF");

	if(nAvgBatteryLevel < NXT_LOW_BAT) nxtDisplayTextLine(2, "***NXT     LOW***");
	if(externalBatteryAvg < EXT_LOW_BAT) nxtDisplayTextLine(2, "***    EXT LOW***");
	if(nAvgBatteryLevel < NXT_LOW_BAT && externalBatteryAvg < EXT_LOW_BAT) nxtDisplayTextLine(2, "***NXT EXT LOW***");

	while(nNxtButtonPressed != BTN_CENTER) { // SIDE: Left | Right | Bridge | None
		     if(OPT_SIDE == 0) nxtDisplayTextLine(3, "SIDE: Left");
		else if(OPT_SIDE == 1) nxtDisplayTextLine(3, "SIDE: Right");
		else if(OPT_SIDE == 2) nxtDisplayTextLine(3, "SIDE: Bridge");
		else if(OPT_SIDE == 3) nxtDisplayTextLine(3, "SIDE: None");

		if(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) {
			PlaySound(soundShortBlip);
			if(nNxtButtonPressed == BTN_LEFT) OPT_SIDE--;
			if(nNxtButtonPressed == BTN_RIGHT) OPT_SIDE ++;
			if(OPT_SIDE > 3) OPT_SIDE = 0;
			if(OPT_SIDE < 0) OPT_SIDE = 3;

			while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
		}
	} PlaySound(soundShortBlip); while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);

	if(OPT_SIDE != 3) // DELAY: 0 - 25000
		while(nNxtButtonPressed != BTN_CENTER) {
			nxtDisplayTextLine(4, "DELY: %i", OPT_DELAY);
			if(nNxtButtonPressed == 1 || nNxtButtonPressed == 2) {
				PlaySound(soundShortBlip);
				if(nNxtButtonPressed == 2) OPT_DELAY -= (time1[T1] < 200 ? 5000 : 1000);
				if(nNxtButtonPressed == 1) OPT_DELAY += (time1[T1] < 200 ? 5000 : 1000);
				if(OPT_DELAY < 0)     OPT_DELAY = 25000;
				if(OPT_DELAY > 25000) OPT_DELAY = 0;

				while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
				ClearTimer(T1);
			}
		} if(OPT_SIDE != 3) PlaySound(soundShortBlip); while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);

	if(OPT_SIDE < 2) // AUTO: IR | Crate 1 | Crate 2 | Crate 3 | Crate 4
		while(nNxtButtonPressed != BTN_CENTER) {
			if(OPT_AUTO == 0) nxtDisplayTextLine(5, "AUTO: IR");
			else nxtDisplayTextLine(5, "AUTO: Crate %i", OPT_AUTO);

			if(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) {
				PlaySound(soundShortBlip);
				if(nNxtButtonPressed == BTN_LEFT) OPT_AUTO--;
				if(nNxtButtonPressed == BTN_RIGHT) OPT_AUTO++;
				if(OPT_AUTO > 4) OPT_AUTO = 0;
				if(OPT_AUTO < 0) OPT_AUTO = 4;

				while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
			}
		} if(OPT_SIDE < 2) PlaySound(soundShortBlip); while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);

	if(OPT_SIDE < 2) // BRIDGE: Closest | Left | Right | Back up | None
		while(nNxtButtonPressed != BTN_CENTER) {
			     if(OPT_BRIDGE == 0) nxtDisplayTextLine(6, "BRDG: Closest");
			else if(OPT_BRIDGE == 1) nxtDisplayTextLine(6, "BRDG: Left");
			else if(OPT_BRIDGE == 2) nxtDisplayTextLine(6, "BRDG: Right");
			else if(OPT_BRIDGE == 3) nxtDisplayTextLine(6, "BRDG: Back up");
			else if(OPT_BRIDGE == 4) nxtDisplayTextLine(6, "BRDG: None");

			if(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) {
				PlaySound(soundShortBlip);
				if(nNxtButtonPressed == BTN_LEFT) OPT_BRIDGE--;
				if(nNxtButtonPressed == BTN_RIGHT) OPT_BRIDGE++;
				if(OPT_BRIDGE > 4) OPT_BRIDGE = 0;
				if(OPT_BRIDGE < 0) OPT_BRIDGE = 4;

				while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
			}
		} if(OPT_SIDE < 2) PlaySound(soundShortBlip); while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);
	nxtDisplayTextLine(7, "*** LOCKED ***");
}

task main() {
	initializeRobot();
	optionScreen();
	//waitForStart();
	wait1Msec(OPT_DELAY);
	     if(OPT_SIDE == 0) runAutoLeft();
	else if(OPT_SIDE == 1) runAutoRight();
	else if(OPT_SIDE == 2) moveToBridge();
	lockdownRobot();
}