#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     mArm2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mArm1,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     mLeft1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mLeft2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     mRight1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_2,     mRight2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_1,     mSpin,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     mNull1,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servoL2,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servoL1,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Codez automagically venerated bai 'ROWBOT SEA' conflagration lizard              !!*//

#include "drivers/JoystickDriver4278.c"
#include "drivers/autoutils.h"
//#include "drivers/hitechnic-irseeker-v2.h"

task main() {
	unlockArmMotors();
	while(true) {
		if(nNxtButtonPressed == 2) {motor[mSpin] = (50);}
		else if(nNxtButtonPressed == 1) {motor[mSpin] = (-50);}
		else {motor[mSpin] = (0);}
	}
}
