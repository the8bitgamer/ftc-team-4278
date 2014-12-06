#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     HTSPB,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_2,     mRight1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     mRight2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     mLeft2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     mLeft1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     mArm1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     mArm2,       tmotorTetrix, openLoop)

//*!!Codez automagically venerated by 'ROWBOAT SEA' conflagration lizard               !!*//

#include "drivers/teleoputils.h"

void invokeButton(int button, bool pressed) {
	switch(button) {
		case BUTTON_X:
			if(pressed)
				{
					motor[mArm1] = 58;
				}
				else
				{
					stopArm();
				}
				break;
		case BUTTON_Y:
			if(pressed)
				{
					motor[mArm1] = -58;
				}
				else
				{
					stopArm();
				}
				break;
			case BUTTON_B:
			if(pressed)
				{
					motor[mArm2] = -58;
				}
				else
				{
					stopArm();
				}
				break;
			case BUTTON_A:
			if(pressed)
				{
					motor[mArm2] = 58;
				}
				else
				{
					stopArm();
				}
				break;
		case BUTTON_LT: if(pressed) {extendArm();} else {stopArm();} break;
		case BUTTON_ST: if(pressed){} else {} break;
		case BUTTON_BA: if(pressed) {} else {} break;
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
  StartTask(monitorFeedback);

 	while(true)
 		{

		getJoystickSettings(joystick);
		checkJoystickButtons();

		if(joystick.joy1_TopHat == -1) {

			setRightMotors((powscl(JOY_Y1) + powscl(JOY_X1))/2.6);
			setLeftMotors((powscl(JOY_Y1) - powscl(JOY_X1))/2.6);
		} else {
			setRightMotors(getRightPowTopHat(joystick.joy1_TopHat));
			setLeftMotors(getLeftPowTopHat(joystick.joy1_TopHat));
		}
	}
}
