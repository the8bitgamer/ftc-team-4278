#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     mLeft1,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     mRight1,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     mShift1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mShift2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mLeft2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     mLeft3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     mRight2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     mRight3,       tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    sShifter,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    sLock,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Codez automagically venerated by 'ROWBOT SEA' conflagration lizard               !!*//

#include "autoconst.h"
#include "drivers/autoutils.h"

int OPT_SIDE = 0; int OPT_DELAY = 0; int OPT_BRIDGE = 0;

void autoCenter() {
	int crate = rbtMoveToIR(2000);
	dumpArm();
	nxtDisplayBigTextLine(3, "%d", crate);
	if(OPT_BRIDGE == 0) if(crate <= 2) OPT_BRIDGE = 2; else OPT_BRIDGE = 1;
	if(OPT_BRIDGE == 4) return;
	if(OPT_BRIDGE == 3) {rbtMoveFdDist(16, 4000); return;}

	if(crate == 1 || crate == 4) rbtMoveFdDistErr(14, 3000);
	if(crate == 2 || crate == 3) rbtMoveFdDistErr(20, 3000);

	if(OPT_BRIDGE == 2) rbtArcRight(-45.0/2.5);
	if(OPT_BRIDGE == 1) rbtArcLeft(  45.0/1.5);

	rbtMoveFdDist(-30, 5000);

	if(OPT_BRIDGE == 2)   rbtArcLeft(120/2.5);
	if(OPT_BRIDGE == 1) rbtArcRight(-120/2.5);

	rbtMoveFdDist(-10, 5000);

	if(OPT_BRIDGE == 2)   rbtArcLeft(90/2.5);
	if(OPT_BRIDGE == 1) rbtArcRight(-90/2.5);

	rbtMoveFdDist(100, -20, 5000);
}

void optionScreen() {
	nxtDisplayTextLine(0, "NXT:  %.2f V", ((float)nAvgBatteryLevel)/1000.0);
	if(externalBatteryAvg > 0) nxtDisplayTextLine(1, "EXT: %.2f V", ((float)externalBatteryAvg)/1000.0);
		else nxtDisplayTextLine(1, "EXT: OFF");

	if(nAvgBatteryLevel < NXT_LOW_BAT) nxtDisplayTextLine(2, "***NXT     LOW***");
	if(externalBatteryAvg < EXT_LOW_BAT) nxtDisplayTextLine(2, "***    EXT LOW***");
	if(nAvgBatteryLevel < NXT_LOW_BAT && externalBatteryAvg < EXT_LOW_BAT) nxtDisplayTextLine(2, "***NXT EXT LOW***");

	while(nNxtButtonPressed != BTN_CENTER) { // SIDE: Center | Bridge | None
				 if(OPT_SIDE == 0) nxtDisplayTextLine(3, "SIDE: Center");
		else if(OPT_SIDE == 1) nxtDisplayTextLine(3, "SIDE: Bridge");
		else if(OPT_SIDE == 2) nxtDisplayTextLine(3, "SIDE: None");

		if(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) {
			PlaySound(soundShortBlip);
			if(nNxtButtonPressed == BTN_LEFT) OPT_SIDE--;
			if(nNxtButtonPressed == BTN_RIGHT) OPT_SIDE ++;
			if(OPT_SIDE > 2) OPT_SIDE = 0;
			if(OPT_SIDE < 0) OPT_SIDE = 2;

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

	if(OPT_SIDE == 0) // BRIDGE: Closest | Left | Right | Back up | None
		while(nNxtButtonPressed != BTN_CENTER) {
			     if(OPT_BRIDGE == 0) nxtDisplayTextLine(5, "BRDG: Closest");
			else if(OPT_BRIDGE == 1) nxtDisplayTextLine(5, "BRDG: Left");
			else if(OPT_BRIDGE == 2) nxtDisplayTextLine(5, "BRDG: Right");
			else if(OPT_BRIDGE == 3) nxtDisplayTextLine(5, "BRDG: Back up");
			else if(OPT_BRIDGE == 4) nxtDisplayTextLine(5, "BRDG: None");

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
	setArmUnlocked();
	//optionScreen();
	//wait1Msec(OPT_DELAY);

	autoCenter();
}
