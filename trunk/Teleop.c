#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sensorIR,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     HTSPB,          sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     mRight2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mRight1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     mLeft1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     mLeft2,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    tubeHook1,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    tubeHook2,            tServoStandard)

//*!!Codez automagically venerated by 'ROWBOAT SEA' conflagration lizard               !!*//

#include "drivers/teleoputils.h"

void invokeButton(int button, bool pressed) {
	switch(button) {
		case BUTTON_ST: if(pressed) {extendArm();} else {stopArm();} break;
		case BUTTON_B:
			if(pressed)
			{
				if(servo[tubeHook1] == HOOK1_HOOKREST)
				{
					servo[tubeHook1] = HOOK1_HOOKDOWN;
				}
				else
				{
					servo[tubeHook1] = HOOK1_HOOKDOWN;
				}
			} else {} break;
		case BUTTON_X:
			if(pressed)
			{
				if(servo[tubeHook2] == HOOK2_HOOKREST)
				{
					servo[tubeHook2] = HOOK2_HOOKDOWN;
				}
				else
				{
					servo[tubeHook2] = HOOK2_HOOKREST;
				}
			} else {} break;

		case BUTTON_A:
			if(pressed)
			{
				activateStopBlocks();
			} else {} break;
		case BUTTON_Y:
			if(pressed) {retractHooks();} else {} break;
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

  //declare variables out here for max speed
  int joyYScaled = 0;
  int joyXScaled = 0;

 	while(true) {
		getJoystickSettings(joystick);
		checkJoystickButtons();

		if(joystick.joy1_TopHat == -1) {

			joyYScaled = powscl(JOY_Y1);

			joyXScaled = powscl(JOY_X1);

			setRightMotors((joyYScaled +joyXScaled)/2.6);
			setLeftMotors((joyYScaled - joyXScaled)/2.6);
		} else {
			setRightMotors(getRightPowTopHat(joystick.joy1_TopHat));
			setLeftMotors(getLeftPowTopHat(joystick.joy1_TopHat));
		}
	}
}
