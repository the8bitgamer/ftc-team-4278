#pragma config(Hubs,  S4, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,	   SMUX,		   sensorI2CCustom)
#pragma config(Sensor, S2,	   sGyr,		   sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,	   sAcc,		   sensorI2CCustomFastSkipStates)
#pragma config(Sensor, S4,	   ,			   sensorI2CMuxController)
#pragma config(Motor,  mtr_S4_C1_1,		motorBL,	   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,		motorFL,	   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,		motorArmE2,	   tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_2,		motorArms,	   tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C3_1,		motorBR,	   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C3_2,		motorFR,	   tmotorTetrix, openLoop, reversed)

#include "AccelGyroDriver.h"
#include "AutoHolonomic.h"
#include "ArmControl.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-irseeker-v2.h"

int cols[3] = {0,0,0};
void getIRColumnTargetData() {
	for(int col=0; col<3; col++)
	{
		int row = 0;
		while(nNxtButtonPressed != 3) {
			nxtDisplayTextLine(2+col, "IR Col %d ==> R%d", col+1, row);
			if(nNxtButtonPressed == 1) {row++; while(nNxtButtonPressed == 1){}}
			if(nNxtButtonPressed == 2) {row--; while(nNxtButtonPressed == 2){}}
			if(row > 3) row = 1; if(row < 1) row = 3;
		}
		cols[col] = row;
		while(nNxtButtonPressed == 3){}
	}
}

int getIRColumn()
{
	int col1 = HTIRS2readACDir(msensor_S1_1);
	int col2 = HTIRS2readACDir(msensor_S1_2);
	int x = (col1==9?(col2==2?1:2):3);
	return x;
}

void autoCol1() {
}

void autoCol2() {
	moveToPos(1.25, 5.25, .5);
	moveToRot(90);
}

void autoCol3() {
	moveToPos(3, 3, .5);
	moveToRot(45);
}

void initializeRobot() {
	nMotorEncoder[motorArms] = 0; nMotorEncoder[motorArmE2] = 0;
	getIRColumnTargetData();
	nxtDisplayTextLine(6, "LOCKED");

	debugAccelGyro = false;
	BackgroundIntegration();
	StartTask(HolonomicControl);
	debugAccelGyro = true;
}

void closeAutonomous() {

}

task main()
{
	initializeRobot();
	/*int irCol = getIRColumn();
	int irRow = cols[irCol-1];
	switch(irRow) {
		case 1: StartTask(armLow); break;
		case 2: StartTask(armMid); break;
		case 3: StartTask(armHi); break;
	}
	if(irCol == 1) autoCol1();
	if(irCol == 2) autoCol2();
	if(irCol == 3) autoCol3();*/

	//moveToWhite(0, 2, .3);
	//resetPositionData();
	ClearTimer(T1); while(time1[T1] < 10000){EndTimeSlice();}
	closeAutonomous();
}
