#pragma config(Hubs,  S4, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     SMUX,           sensorI2CCustom)
#pragma config(Sensor, S2,     sGyr,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     sAcc,           sensorI2CCustomFastSkipStates)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S4_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,     motorAmrL,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_2,     motorAmrR,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C3_1,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C3_2,     motorFR,       tmotorTetrix, openLoop, reversed)

#include "AccelGyroDriver.h"
#include "AutoHolonomic.h"
#include "ArmControl.h"
#include "AutoManager.h"

#include "drivers/hitechnic-colour-v2.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"

int getIRColumn(int defaultIfErr) {
	ClearTimer(T4); int col = -1;
	while(col == -1 && time1[T4] < 1500) {
		int col1 = HTIRS2readACDir(msensor_S1_1);
		int col2 = HTIRS2readACDir(msensor_S1_2);
		nxtDisplayTextLine(4, "c1: %i c2: %i", col1, col2);
		if(col1 == 3 && col2 == 6) col = 3;
		if(col1 == 3 && col2 == 5) col = 2;
		if(col1 == 2 && col2 == 5) col = 1;
		nxtDisplayTextLine(3, "%i", col);
	}
	return (col==-1?defaultIfErr:col);
}

void getAutoPowerErrs() {
	int _r, _g, _b; HTCS2readRGB(msensor_S1_3, _r, _g, _b);
	if(_r + _g + _b == 255*3) {nxtDisplayTextLine(1, "TURN ON SMUX");} else {nxtDisplayTextLine(1, "             ");}

	if(externalBatteryAvg < 12600) {nxtDisplayTextLine(0, "REPLACE TXBATT");}
	else {nxtDisplayTextLine(0, "N:%f T:%f", ((float)nAvgBatteryLevel)/1000.0, ((float)externalBatteryAvg)/1000.0);}
	if(externalBatteryAvg == -1) {nxtDisplayTextLine(0, "TURN ON TXBATT");}
}

int autoType = 1; bool autoUseIRData = true; int autoColTarget = 2; int autoMsecDelay = 0; int autoColIRErr = 2; int armLevel = 4;
void getAutoUserData() {
	while(nNxtButtonPressed != 3) {
		getAutoPowerErrs();
		if(autoType == autoFront || autoType == -1) nxtDisplayTextLine(2, "Auton: Front ");
		if(autoType == autoBack) nxtDisplayTextLine(2, "Auton: Back  ");
		if(autoType == autoDef) nxtDisplayTextLine(2, "Auton: Defend");
		if(nNxtButtonPressed == 1) {autoType--; if(autoType < 1) autoType = 3; while(nNxtButtonPressed == 1);}
		if(nNxtButtonPressed == 2) {autoType++; if(autoType > 3) autoType = 1; while(nNxtButtonPressed == 2);}
	} while(nNxtButtonPressed == 3);

	while(nNxtButtonPressed != 3) {
		getAutoPowerErrs();
		nxtDisplayTextLine(3, "Delay: %i     ", autoMsecDelay);
		if(nNxtButtonPressed == 1) {autoMsecDelay += 500; while(nNxtButtonPressed == 1);}
		if(nNxtButtonPressed == 2) {autoMsecDelay -= 500; while(nNxtButtonPressed == 2);}
	} while(nNxtButtonPressed == 3);

	while(nNxtButtonPressed != 3) {
		getAutoPowerErrs();
		if(autoUseIRData)  nxtDisplayTextLine(4, "UseIR: Yes");
		if(!autoUseIRData) nxtDisplayTextLine(4, "UseIR: No ");
		if(nNxtButtonPressed == 1 || nNxtButtonPressed == 2) {autoUseIRData = !autoUseIRData; while(nNxtButtonPressed != -1);}
	} while(nNxtButtonPressed == 3);

	if(autoUseIRData == false) {
		autoColTarget = 1;
		while(nNxtButtonPressed != 3) {
			getAutoPowerErrs();
			nxtDisplayTextLine(5, "Colmn: Col%i", autoColTarget);
			if(nNxtButtonPressed == 2) {autoColTarget--; if(autoColTarget < 1) autoColTarget = 3; while(nNxtButtonPressed == 2);}
			if(nNxtButtonPressed == 1) {autoColTarget++; if(autoColTarget > 3) autoColTarget = 1; while(nNxtButtonPressed == 1);}
		}
	} else {
		autoColIRErr = 1;
		while(nNxtButtonPressed != 3) {
			getAutoPowerErrs();
			nxtDisplayTextLine(5, "OnErr: Col%i", autoColIRErr);
			if(nNxtButtonPressed == 2) {autoColIRErr--; if(autoColIRErr < 1) autoColIRErr = 3; while(nNxtButtonPressed == 2);}
			if(nNxtButtonPressed == 1) {autoColIRErr++; if(autoColIRErr > 3) autoColIRErr = 1; while(nNxtButtonPressed == 1);}
		}
	} while(nNxtButtonPressed == 3);

	while(nNxtButtonPressed != 3) {
		getAutoPowerErrs();
		nxtDisplayTextLine(6, "Hight: %s", (armLevel == 2 ? "Mid" : "Top"));
		if(armLevel == 4) nxtDisplayTextLine(6, "Hight: Def");
		if(nNxtButtonPressed == 2) {armLevel--; if(armLevel < 2) armLevel = 4; while(nNxtButtonPressed == 2);}
		if(nNxtButtonPressed == 1) {armLevel++; if(armLevel > 4) armLevel = 2; while(nNxtButtonPressed == 1);}
	}
	nxtDisplayTextLine(7, "Settings LOKI\'D");
}

void getAutoNumber(int irCol) {
	switch(autoType) {
		case autoFront:
			if(autoColTarget == 1) currentAuton = autoVF1;
			if(autoColTarget == 2) currentAuton = autoVF2;
			if(autoColTarget == 3) currentAuton = autoVF3;
			break;
		case autoBack:
			if(autoColTarget == 1) currentAuton = autoVB1;
			if(autoColTarget == 2) currentAuton = autoVB2;
			if(autoColTarget == 3) currentAuton = autoVB3;
			break;
		case autoDef:
			if(autoColTarget == 1) currentAuton = autoVD1;
			if(autoColTarget == 2) currentAuton = autoVD2;
			if(autoColTarget == 3) currentAuton = autoVD3;
			break;
	}

	if(armLevel == 4) {
		if(autoColTarget == 1) armTargetLevel = 3;
		if(autoColTarget == 2) armTargetLevel = 2;
		if(autoColTarget == 3) armTargetLevel = 3;
	}
	else {armTargetLevel = armLevel;}
}

void initializeRobot() {
	eraseDisplay();
	getAutoUserData();
	waitForStart();

	if(autoUseIRData) autoColTarget = getIRColumn(autoColIRErr);
	wait1Msec(autoMsecDelay);

	hogCPU(); bDisplayDiagnostics = false; eraseDisplay();
	getAutoNumber(autoColTarget);
	initializeAccelGyro();
}

task main() {
	initializeRobot();
	//ClearTimer(T2); while(!moveToPos(0,2,1) && time1[T2] < 3000) {BackgroundIntegrator();} StopAllTasks();
	while(true) {
		BackgroundIntegrator();
		AutonomousManager();
		RunArmState();
	}
}
