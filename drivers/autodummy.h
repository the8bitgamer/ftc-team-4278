#ifndef __AUTOUTILS__
#define __AUTOUTILS__
#define __AUTODUMMY__

#include "sharedutils.h"

#define DRV_TIMER T3
#define MAX_TURN_TIME 3000
#define PAUSE_TIME 160

void pause() {wait1Msec(PAUSE_TIME);}
void pause(int n) {for(int i = 0; i < n; i++) pause();}
void estop() {StopAllTasks();}

int getEncoderByInches(float inches) {return floor((1440)*(abs(inches))/WHEELCIRC);}
float getInchesByEncoder(int encode) {return (((float)abs(encode))/1440.0)*WHEELCIRC;}

int linePtr = -1;
int linePoint() {
	linePtr = (linePtr == 7 ? 0 : linePtr + 1);
	if(linePtr == 0) eraseDisplay();
	return linePtr;
}

void waitForButton() {
	while(nNxtButtonPressed != BTN_CENTER) wait1Msec(5);
	PlaySound(soundShortBlip);
	while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);
}

void dumpArm() {
	nxtDisplayTextLine(linePoint(), "Arm dump");
	waitForButton();
}

void lockdownRobot() {
	nxtDisplayTextLine(linePoint(), "Lockdown robot");
	waitForButton();
}

int rbtMoveToIR(int max, int timeout) {
	nxtDisplayTextLine(linePoint(), "MveIR %i", max);
	waitForButton();
	return C1_ENC;
}

void rbtMoveFdDist(float inches, int msec) {
	nxtDisplayTextLine(linePoint(), "MveFD %.2f", inches);
	waitForButton();
}
void rbtMoveFdEnc(int enc, int msec) {rbtMoveFdDist(getInchesByEncoder(enc), msec);}

void rbtArcLeft(float degs) {
	nxtDisplayTextLine(linePoint(), "RbtAL %.1f", degs);
	waitForButton();
}

void rbtArcRight(float degs) {
	nxtDisplayTextLine(linePoint(), "RbtAR %.1f", degs);
	waitForButton();
}

void rbtTurnRight(float degs) {
	nxtDisplayTextLine(linePoint(), "RbtTR %.1f", degs);
	waitForButton();
}

void rbtTurnLeft(float degs) {
	nxtDisplayTextLine(linePoint(), "RbtTL %.1f", degs);
	waitForButton();
}

#endif //__AUTOUTILS___
