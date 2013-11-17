#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     mRight1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mRight2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     mArm2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mSpin,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mLeft1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     mLeft2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     mArm1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servoL1,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servoL2,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code autocratically exonerated by 'ROBOTC' configuration lizard               !!*//

#include "drivers/autoutils.h"
#include "drivers/hitechnic-irseeker-v2.h"
//crt4, crt3, crt2, crt1
#define AOPINIT 0
#define AOPCRT1 1
#define AOPCRT2 2
#define AOPCRT3 3
#define AOPCRT4 4
#define AOPSCORE 5
#define AOPEND 99

int subindex = 0;
void setSubindex(int sind) {subindex = sind;}
int operatingIndex = AOPINIT;
void setOperIndex(int action) {operatingIndex = action; subindex = 0; wait1Msec(250);}

void initialize() {
	unlockArmMotors();
	setOperIndex(AOPCRT2);
}

void moveCenterCrate(bool left) {
	clearEncoders();
	setLeftMotors((left?0:-40));setRightMotors((left?-40:0) while((left?rightEncoder:leftEncoder) < getEncoderByInches(4.5));
	clearEncoders();
	setLeftMotors(-40); setRightMotors(-40); while(rightEncoder < getEncoderByInches(50)); setRightMotors(0); setLeftMotors(0);
	setOperIndex(AOPSCORE);
}

void moveOutsideCrate() {
	clearEncoders();
	setLeftMotors(-40); while(leftEncoder < getEncoderByInches(4.5)); setLeftMotors(0);
	wait1Msec(500);

	clearEncoders();
	setLeftMotors(-40); setRightMotors(-40); while(rightEncoder < getEncoderByInches(50)); setRightMotors(0); setLeftMotors(0);
	setOperIndex(AOPSCORE);
}

task main() {
	displayDiagnostics();
	bool error = false;
	while(!collisionCheck() && !error) {
		switch(operatingIndex) {
			case AOPINIT: initialize(); break;
			case AOPCRT1: moveCrateCenter(); break;
			case AOPCRT2: moveCrateCenter(); break;
			case AOPEND : wait1Msec(100); break;

			default: lockdownRobot();
		}
	}
}
