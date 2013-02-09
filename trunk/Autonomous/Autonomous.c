#pragma config(Hubs,  S4, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     SMUX,           sensorI2CCustom)
#pragma config(Sensor, S2,     htGyro,         sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S4_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,     motorAmrL,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_2,     motorAmrR,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C3_1,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C3_2,     motorFR,       tmotorTetrix, openLoop, reversed)

#define irThreshold 50
#define irMinThreshold 10

#define wheelSeparation 17.0
#define wheelSize 3.0

#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "ArmControl.h"

void motorsAll(int pw) {
	motor[motorFR] = -pw;
	motor[motorBR] = -pw;
	motor[motorFL] = -pw;
	motor[motorBL] = -pw;
}

void motorsLeft(int pw) {
	motor[motorFL] = pw;
	motor[motorBL] = pw;
}

void motorsRight(int pw) {
	motor[motorFR] = pw;
	motor[motorBR] = pw;
}

void moveRot(float degs) {
	nMotorEncoder[motorBL] = 0;
	float targetEnc = ((degs/(PI*wheelSeparation)) / (3.0*PI))*1440.0*4*3.1415926535897932384626433832750;
	while(abs(nMotorEncoder[motorBL]) < abs(targetEnc)) {
	motorsLeft(50*(degs>0?1.0:-1.0));
	motorsRight(50*(degs>0?-1.0:1.0));
		nxtDisplayTextLine(5, "%i", nMotorEncoder[motorBL]);
	}
	motorsAll(0);
}

const tMUXSensor g = msensor_S1_1;
const tMUXSensor g2 = msensor_S1_2;

void debugIRDir() {
	while(true) {
		nxtDisplayTextLine(3, "%i", HTIRS2readACDir(g));
		nxtDisplayTextLine(4, "%i", HTIRS2readACDir(g2));
	}
}

int readIRDir() {
	if(HTIRS2readACDir(g) == 7 && HTIRS2readACDir(g2) == 1) return 1;
	if(HTIRS2readACDir(g) == 0 && HTIRS2readACDir(g2) == 0) return 2;
	if((HTIRS2readACDir(g) == 8 || HTIRS2readACDir(g) == 9) && HTIRS2readACDir(g2) == 2) return 3;
	else return 2;
}

void runArmDown() {
	ClearTimer(T1);
	while(time1[T1] < 300) {
		motorArmL = -15;
		motorArmR = -15;
	}
	motorArmL = 0;
	motorArmR = 0;
}

void aCR() {moveRot(11.5); wait1Msec(500); motorsAll(100); ClearTimer(T1); while(time1[T1] < 3500) {RunArmState();} motorsAll(0); wait1Msec(100); runArmDown(); wait1Msec(250); motorsAll(-50); wait1Msec(500);}
void aCM() {motorsAll(100); ClearTimer(T1); while(time1[T1] < 3500) {RunArmState();} motorsAll(0); wait1Msec(100); runArmDown(); wait1Msec(250); motorsAll(-50); wait1Msec(500);}
void aCL() {moveRot(-18.5); wait1Msec(500); motorsAll(100); ClearTimer(T1); while(time1[T1] < 3500) {RunArmState();} motorsAll(0); wait1Msec(100); runArmDown(); wait1Msec(250); motorsAll(-50); wait1Msec(500);}
void aDL() {motorsAll(100); wait1Msec(2500); moveRot( 30); motorsAll(100); wait1Msec(1500);}
void aDR() {motorsAll(100); wait1Msec(2500); moveRot(-65); motorsAll(100); wait1Msec(1500);}

task main() {
	//debugIRDir();
	int col = readIRDir();
	if(col == 1) aCR();
	if(col == 2) aCM();
	if(col == 3) aCL();
}
