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

#include "drivers/JoystickDriver4278.c"
#include "drivers/autoutils.h"
#include "drivers/hitechnic-irseeker-v2.h"

#define DrTimer T3
#define SeTimer T2

void rbtMoveFd(float inches) {
	int enc = getEncoderByInches(inches); clearEncoders();
	int norm = -1.0*sgn(inches);

	while(leftEncoder < enc || rightEncoder < enc) {
		setLeftMotors (40*norm);
		setRightMotors(40*norm);
	}
	setLeftMotors(0); setRightMotors(0);
}

void rbtMoveFdTime(float inches, int msec) {
	int enc = getEncoderByInches(inches); clearEncoders();
	int norm = -1.0*sgn(inches);
	ClearTimer(DrTimer);
	while(leftEncoder < enc && rightEncoder < enc && time1[DrTimer] < msec) {
		setLeftMotors (100*norm);
		setRightMotors(100*norm);
	}
	setLeftMotors(0); setRightMotors(0);
}

void rbtArcLeft(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(-1*sgn(degs)*35);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0);
}

void rbtArcRight(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setRightMotors(sgn(degs)*35);
	while(rightEncoder < enc) wait1Msec(10);
	setRightMotors(0);
}

void rbtTurnRight(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors( -1*sgn(degs)*30);
	setRightMotors(sgn(degs)*30);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

void rbtTurnLeft(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*30);
	setRightMotors(-1*sgn(degs)*30);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

void dumpArm() {
	setArmMotors(50);
	wait1Msec(1550);
	setArmMotors(0);
	wait1Msec(400);
	setArmMotors(-50);
	wait1Msec(900);
	setArmMotors(0);
}

void normstop() {while(true) wait1Msec(100);}
void estop() {StopAllTasks();}
void pause() {wait1Msec(175);}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Start Autonomous Fucntions
 *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

void leftBridge(float bridgeDist){
	rbtArcRight(90); pause();
	rbtMoveFd(bridgeDist); pause();
	rbtArcRight(-90); pause();
	rbtMoveFd(18); pause();
	rbtArcRight(-94); pause();
	rbtMoveFdTime(25, 5000);
	normstop();
}

void rightBridge(float bridgeDist){
	rbtArcLeft(-90); pause();
	rbtMoveFd(bridgeDist); pause();
	rbtArcLeft(88); pause();
	rbtMoveFd(18); pause();
	rbtArcLeft(94); pause();
	rbtMoveFdTime(25, 5000);
	normstop();
}

void crateOne(){
	rbtArcLeft(26.0); pause();
	rbtMoveFd(35); pause();
	rbtArcRight(-24.0); pause();
	dumpArm();
	leftBridge(11.5);
}

void crateTwo(){
	rbtArcLeft(16); pause();
	rbtMoveFd(32); pause();
	rbtArcRight(-15); pause();
	dumpArm();
	leftBridge(18.5);
}

void crateThree(){
	rbtArcRight(-8.3); pause();
	rbtMoveFd(34); pause();
	rbtArcLeft(14.7); pause();
	dumpArm(); rightBridge(22.0);
}

void crateFour(){
	rbtArcRight(-22.5); pause();
	rbtMoveFd(35); pause();
	rbtArcLeft(22.5); pause();
	dumpArm(); rightBridge(12.0);
}

void initializeRobot(){
	unlockArmMotors();
}

int crateButtons() {
	int crate = 0;
	while(!nNxtButtonPressed == BTN_CENTER) {
		if(crate > 0) nxtDisplayTextLine(3, "Crate? %i", crate);
		else nxtDisplayTextLine(3, "Crate? IR");
		if(nNxtButtonPressed == BTN_LEFT)  {crate--; while(nNxtButtonPressed == BTN_LEFT);}
		if(nNxtButtonPressed == BTN_RIGHT) {crate++; while(nNxtButtonPressed == BTN_RIGHT);}
		if(crate < 0) crate = 4; if(crate > 4) crate = 0;
	}
	return crate;
}

int crateIR(){};

void crateSelect(int crate){
	     if(crate == 0) crate = crateIR();
			 if(crate == 1) crateOne();
	else if(crate == 2) crateTwo();
	else if(crate == 3) crateThree();
	else if(crate == 4) crateFour();

	StopAllTasks();
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * End Autonomous Fucntions
 *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

task main() {
	displayDiagnostics();
	initializeRobot();
	int crate = 4;//crateButtons();
	waitForStart();
	crateSelect(crate);
}
