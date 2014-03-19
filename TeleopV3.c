#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     mLeft1,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     mRight1,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     mShift1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mShift2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     mLeft2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     mLeft3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     mRight2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     mRight3,       tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    sShifter,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    sLock,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Codez automagically venerated by 'ROWBOT SEA' conflagration lizard               !!*//

#include "drivers/teleoputils.h"

void invokeButton(int button, bool pressed) {
	switch(button) {
		case JOY_X:  if(pressed) {} else {} break;
		case JOY_Y:  if(pressed) {} else {} break;
		case JOY_A:  if(pressed) {} else {} break;
		case JOY_B:  if(pressed) {setShifterFlag(); setShiftMotors(100);} else {setShiftMotors(0);} break;

		case JOY_RB: if(pressed) {setShifterArm(); setShiftMotors(-60);}  else {setShiftMotors(0);} break;
		case JOY_LB: if(pressed) {setShifterArm(); setShiftMotors(100);} else {setShiftMotors(0);} break;
		case JOY_RT: if(pressed) {setArmUnlocked();} else {} break;
		case JOY_LT: if(pressed) {setArmLocked();} else {} break;

		case JOY_R3: if(pressed) {} else {} break;
		case JOY_L3: if(pressed) {} else {} break;
		case JOY_ST: if(pressed) {} else {} break;
		case JOY_BA: if(pressed) {} else {} break;
	}
}

short btn = JOY_BTN;
void checkJoystickButtons() {
	if(btn == JOY_BTN) return;
	for(short i = 11; i >= 0; i--) {
		if((btn>>i) ^ (JOY_BTN>>i)) {
			invokeButton(i, ((btn & (1 << i)) == 0));
			btn ^= 1<<i;
		}
	}
}

task main() {
	setShifterArm();
	setArmUnlocked();
	//waitForStart();

 	while(true) {
		getJoystickSettings(joystick);
		checkJoystickButtons();

		if(joystick.joy1_TopHat == -1) {
			setRightMotors(-RIGHT_POW_DIFF*(powscl(JOY_Y1)+powscl(JOY_X1)/2.6));
			setLeftMotors(-LEFT_POW_DIFF*(powscl(JOY_Y1)-powscl(JOY_X1)/2.6));
		} else {
			setRightMotors(getRightPowTopHat(joystick.joy1_TopHat));
			setLeftMotors(getLeftPowTopHat(joystick.joy1_TopHat));
		}

		//nxtDisplayTextLine(3, "RE: %i", rightEncoder);
		//nxtDisplayTextLine(4, "LE: %i", leftEncoder);
	}
}
