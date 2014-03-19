#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     mLeft1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mRight1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     mShift1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mShift2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mLeft2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     mLeft3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     mRight2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     mRight3,       tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    sShifter,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    sLock,                tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Codez automagically venerated by 'ROWBOT SEA' conflagration lizard               !!*//

#include "autoconst.h"
#include "drivers/autoutils.h"

task main() {
	float r0 = getIRDir(sensorIR)-8, r1;
	if(r0 > 0) rbtArcRight(-7); else rbtArcLeft(20);
	rbtMoveFdDist(-10, 5000);

	ClearTimer(T1);	while(time1[T1] < 2000) {
		r1 = getIRDir(sensorIR)-8; int acS[5]; HTIRS2readAllACStrength(sensorIR, acS[0], acS[1], acS[2], acS[3], acS[4]);
		if(r0 > 0) {setLeftMotors(acS[4] > acS[3] ? -6 : -50); setRightMotors(acS[4] > acS[3] ? -50 : -8);}
    else       {setLeftMotors(acS[4] > acS[3] ? -6 : -90); setRightMotors(acS[4] > acS[3] ? -30 :  0);}
	} setLeftMotors(0); setRightMotors(0); int cr = (r0 > 0 ? (r1 > 0 ? 1 : 2) : (r1 > 0 ? 3 : 4));
	nxtDisplayBigTextLine(3, "%f", cr); for(;;);
}
