#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     mArm2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mArm1,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     mRight1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     mRight2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_1,     mLeft1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     mLeft2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,     mSpin,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     mNull1,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servoL2,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servoL1,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Codez automagically venerated by 'ROWBOT SEA' conflagration lizard               !!*//

#include "drivers/autoutils.h"
#include "autoconst.h"
#define POST_BRIDGE true

void initializeRobot() {unlockArmMotors();}

void moveBridge() {
	setLeftMotors(60);
	setRightMotors(60);
	wait1Msec(3200);
	setLeftMotors(0);
	setRightMotors(0);
}

void leftCrate1() {
	rbtMoveFdTime(3.5, 2000); pause(1); //Realign
	rbtArcRight(96); pause(1);          //Turn to crate
	rbtMoveFdTime(-5, 2000); pause(1);  //Run into crate
	dumpArm(); pause(1);                //Dump arm
	rbtMoveFdTime(1, 2000); pause(1);   //Back up
	if(POST_BRIDGE) {
		rbtArcLeft(88); pause(1);           //Turn to bridge
		rbtMoveFdTime(-15.5, 4000); pause(1); //Move away from crates
		rbtArcLeft(-90); pause(1);          //Turn to bridge
		rbtMoveFdTime(-18, 4000); pause(1); //Move in align w/ bridge
		rbtArcLeft(-90); pause(1);          //Turn to bridge
		rbtMoveFdTime(-26, 4000); pause(1); //Onto bridge
	}
}

void leftCrate2() {
	rbtMoveFdTime(4.5, 1000);           //Realign
	rbtArcRight(96); pause(1);          //Turn to crate
	rbtMoveFdTime(-5, 2000); pause(1);  //Run into crate
	dumpArm(); pause(1);                //Dump arm
	rbtMoveFdTime(1, 2000); pause(1);   //Back up
	if(POST_BRIDGE) {
		rbtArcLeft(88); pause(1);           //Turn to bridge
		rbtMoveFdTime(-26, 4000); pause(1); //Move away from crates
		rbtArcLeft(-90); pause(1);          //Turn to bridge
		rbtMoveFdTime(-18, 4000); pause(1); //Move in align w/ bridge
		rbtArcLeft(-95); pause(1);          //Turn to bridge
		rbtMoveFdTime(-26, 4000); pause(1); //Onto bridge
	}
}

void leftCrate3() {
	rbtMoveFdTime(0.5, 1000);           //Realign
	rbtArcRight(96); pause(1);          //Turn to crate
	rbtMoveFdTime(-5, 2000); pause(1);  //Run into crate
	dumpArm(); pause(1);                //Dump arm
	rbtMoveFdTime(1, 2000); pause(1);   //Back up
	if(POST_BRIDGE) {
		rbtArcRight(-88); pause(1);         //Turn to bridge
		rbtMoveFdTime(-21, 4000); pause(1); //Move away from crates
		rbtArcRight(90); pause(1);          //Turn to bridge
		rbtMoveFdTime(-18, 4000); pause(1); //Move in align w/ bridge
		rbtArcRight(90); pause(1);          //Turn to bridge
		rbtMoveFdTime(-26, 4000); pause(1); //Onto bridge
	}
}

void leftCrate4() {
	rbtArcRight(96); pause(1);          //Turn to crate
	rbtMoveFdTime(-5, 2000); pause(1);  //Run into crate
	dumpArm(); pause(1);                //Dump arm
	rbtMoveFdTime(1, 2000); pause(1);   //Back up
	if(POST_BRIDGE) {
		rbtArcRight(-88); pause(1);         //Turn to bridge
		rbtMoveFdTime(-12, 4000); pause(1); //Move away from crates
		rbtArcRight(90); pause(1);          //Turn to bridge
		rbtMoveFdTime(-18, 4000); pause(1); //Move in align w/ bridge
		rbtArcRight(90); pause(1);          //Turn to bridge
		rbtMoveFdTime(-26, 4000); pause(1); //Onto bridge
	}
}

/*void rightCrate1() {
	//rbtMoveFdTime(3, 2000); pause(1);   //Realign
	rbtArcLeft(-96); pause(1);          //Turn to crate
	rbtMoveFdTime(-5, 2000); pause(1);  //Run into crate
	dumpArm(); pause(1);                //Dump arm
	rbtMoveFdTime(1, 2000); pause(1);   //Back up
	if(POST_BRIDGE) {
		rbtArcRight(-88); pause(1);         //Turn to bridge
		rbtMoveFdTime(-15, 4000); pause(1); //Move away from crates
		rbtArcRight(90); pause(1);          //Turn to bridge
		rbtMoveFdTime(-18, 4000); pause(1); //Move in align w/ bridge
		rbtArcRight(90); pause(1);          //Turn to bridge
		rbtMoveFdTime(-26, 4000); pause(1); //Onto bridge
	}
}*/

void runAutoLeft() {
	int dirIR, strIR; float stopRightEnc;
	HTIRS2readEnhanced(sensorIR, dirIR, strIR);
	clearEncoders();

	while(dirIR != 5 && rightEncoder < 4325) {
		HTIRS2readEnhanced(sensorIR, dirIR, strIR);
		stopRightEnc = rightEncoder;
		if(dirIR != 5) {setLeftMotors(60); setRightMotors(60);}
	}
	setLeftMotors(0); setRightMotors(0); pause(3);

	     if(rightEncoder < LC12_THRESH)  leftCrate1();
	else if(rightEncoder < LC23_THRESH) leftCrate2();
	else if(rightEncoder < LC34_THRESH) leftCrate3();
	else                         leftCrate4();
}

/*void runAutoRight() {
	int dirIR, strIR; float stopRightEnc;
	HTIRS2readEnhanced(sensorIR, dirIR, strIR);
	clearEncoders();

	while(dirIR != 5 && rightEncoder < 5850) {
		HTIRS2readEnhanced(sensorIR, dirIR, strIR);
		stopRightEnc = rightEncoder;
		if(dirIR != 5) {setLeftMotors(60); setRightMotors(60);}
		//nxtDisplayBigTextLine(0,"%d",rightEncoder);
	}
	setLeftMotors(0); setRightMotors(0); pause(3);

	     if(rightEncoder < 1835) rightCrate1();
	else if(rightEncoder < 3601) nxtDisplayTextLine(0, "2"); //rightCrate2();
	else if(rightEncoder < 5366) nxtDisplayTextLine(0, "3"); //rightCrate3();
	else                         nxtDisplayTextLine(0, "4"); //rightCrate4();
}*/

int side = 0; int auto = 0; int delay = 0;
void optionScreen() {
	nxtDisplayTextLine(0, "NXT: %f", ((float)nAvgBatteryLevel)/1000.0);
	if(externalBatteryAvg > 0) nxtDisplayTextLine(1, "EXT: %f", ((float)externalBatteryAvg)/1000.0);
		else nxtDisplayTextLine(1, "EXT: **OFF**");

	if(nAvgBatteryLevel < 8000) nxtDisplayTextLine(2, "***NXT     LOW***");
	if(externalBatteryAvg < 12500) nxtDisplayTextLine(2, "***    EXT LOW***");
	if(nAvgBatteryLevel < 8000 && externalBatteryAvg < 12500) nxtDisplayTextLine(2, "***NXT EXT LOW***");

	while(nNxtButtonPressed != BTN_CENTER) {
		if(side == 0) nxtDisplayTextLine(3, "SIDE: Left");
		if(side == 1) nxtDisplayTextLine(3, "SIDE: Right");
		if(side == 2) nxtDisplayTextLine(3, "SIDE: Bridge");
		if(side == 3) nxtDisplayTextLine(3, "SIDE: None");
		if(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) {
			if(nNxtButtonPressed == BTN_LEFT) side--;
			if(nNxtButtonPressed == BTN_RIGHT) side++;
			if(side > 4) side = 0;
			if(side < 0) side = 4;
			while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
		}
	} while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);

	if(side != 3)
		while(nNxtButtonPressed != BTN_CENTER) {
			nxtDisplayTextLine(4, "DELY: %i", delay);
			if(nNxtButtonPressed == 1 || nNxtButtonPressed == 2) {
				if(nNxtButtonPressed == 2) delay -= 1000;
				if(nNxtButtonPressed == 1) delay += 1000;
				if(delay < 0) delay = 25000;
				if(delay > 25000) delay = 0;
				while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
			}
		} while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);

	if(side < 2)
		while(nNxtButtonPressed != BTN_CENTER) {
			if(auto == 0) nxtDisplayTextLine(5, "AUTO: IR");
			else nxtDisplayTextLine(5, "AUTO: Crate %i", auto);

			if(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) {
				if(nNxtButtonPressed == BTN_LEFT) auto--;
				if(nNxtButtonPressed == BTN_RIGHT) auto++;
				if(auto > 4) auto = 0;
				if(auto < 0) auto = 4;
				while(nNxtButtonPressed == BTN_LEFT || nNxtButtonPressed == BTN_RIGHT) wait1Msec(5);
			}
		} while(nNxtButtonPressed == BTN_CENTER) wait1Msec(5);

	nxtDisplayTextLine(7, "*** LOCKED ***");
}

task main() {
	initializeRobot();
	optionScreen();
	waitForStart();
	wait1Msec(delay);

	if(side == 0) { //Left
		if(auto == 0) {runAutoLeft(); lockdownRobot();} //IR

		int encDist = 0;
		if(auto == 1) encDist = LC1_ENC;
		if(auto == 2) encDist = LC2_ENC;
		if(auto == 3) encDist = LC3_ENC;
		if(auto == 4) encDist = LC4_ENC;
		rbtMoveFdTime(getInchesByEncoder(encDist), 5000);
		if(auto == 1) leftCrate1();
		if(auto == 2) leftCrate2();
		if(auto == 3) leftCrate3();
		if(auto == 4) leftCrate4();
	} else if(side == 1) { //Right
	} else if(side == 2) moveBridge(); //Bridge

	lockdownRobot();
}
