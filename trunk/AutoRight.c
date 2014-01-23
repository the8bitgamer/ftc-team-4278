#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     mArm1,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     mArm2,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     mRight1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mRight2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mSpin,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     mLeft1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     mLeft2,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    servoL2,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servoL1,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Codez automagically venerated bai 'ROWBOT SEA' conflagration lizard              !!*//

#include "drivers/wiringnxt.h"
#include "drivers/JoystickDriver4278.c"
#include "drivers/autoutils.h"
#include "drivers/hitechnic-irseeker-v2.h"

#define INIT_PAUSE 0

void rightBridge(float bridgeDist){
	rbtMoveFdTime(bridgeDist, 5000); pause();
	rbtArcRight(-88); pause();
	rbtMoveFdTime(19, 4000); pause();
	rbtArcRight(-90); pause();
	rbtMoveFdTime(25, 5000);
	normstop();
}

void leftBridge(float bridgeDist){
	rbtMoveFdTime(bridgeDist, 5000); pause();
	rbtArcLeft(90); pause();
	rbtMoveFdTime(18, 4000); pause();
	rbtArcLeft(100); pause();
	rbtMoveFdTime(31, 5000);
	normstop();
}

void farLeftBridge(float bridgeDist){
	rbtMoveFdTime(-bridgeDist, 5000); pause();
	rbtArcRight(90); pause();
	rbtMoveFdTime(-20, 4000); pause();
	rbtArcLeft(-90); pause();
	rbtMoveFdTime(37, 5000);
	normstop();
}

void farRightBridge(float bridgeDist){
	rbtMoveFdTime(-bridgeDist, 5000); pause();
	rbtArcLeft(-89); pause();
	rbtMoveFdTime(-22, 4000); pause();
	rbtArcRight(90); pause();
	rbtMoveFdTime(40, 5000);
	normstop();
}

void crateOne(){
	rbtMoveFdTime(-0.756, 1200);
	rbtArcRight(95.5); pause();
	rightBridge(11);
}

void crateTwo(){
	rbtMoveFdTime(-0.756, 1200);
	rbtArcRight(85); pause();
	rightBridge(22);
}

void crateThree(){
	rbtMoveFdTime(-0.756, 1200);
	rbtArcLeft(-90); pause();
	leftBridge(19);
}

void crateFour(){
	rbtMoveFdTime(-1, 1200); pause();
	rbtArcLeft(-90); pause();
	leftBridge(12.5);
}

void initializeRobot() {unlockArmMotors();}

void crateSelect(int crate){
	int dirIR, strIR; float in;
	HTIRS2readEnhanced(sensorIR, dirIR, strIR);
	clearEncoders();

	while(dirIR != 5) {
		HTIRS2readEnhanced(sensorIR, dirIR, strIR);
		in = rightEncoder;
		if(dirIR != 5) {setLeftMotors(-60); setRightMotors(-50);}
		//nxtDisplayBigTextLine(3,"%d",rightEncoder);
	}
	setLeftMotors(0); setRightMotors(0); pause(3);

	if(in < 250) {
		rbtArcRight(-90);
		pause();
		rbtMoveFdTime(4.5, 1000);
		pause(2);
		dumpArm();
		crateFour();
	} else if(in < 1250) {
		rbtMoveFdTime(-0.75, 1000);
		rbtArcRight(-90);
		pause();
		rbtMoveFdTime(5, 1000);
		pause(2);
		dumpArm();
		/*crateThree();*/
	} else if(in < 3000) {
		rbtMoveFdTime(0.5, 1000);
		rbtArcRight(-90);
		pause();
		rbtMoveFdTime(5, 1000);
		pause(2);
		dumpArm();
		crateTwo();
	} else if(in < 5000) {
		rbtMoveFdTime(3.0, 1000);
		rbtArcRight(-90);
		pause();
		rbtMoveFdTime(5, 1000);
		pause(2);
		dumpArm();
		crateOne();
	}
	StopAllTasks();
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * End Autonomous Fucntions
 *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

task main() {
	displayDiagnostics();
	initializeRobot();
	waitForStart();
	wait1Msec(INIT_PAUSE);
	int crate = 0;
	crateSelect(crate);
}
