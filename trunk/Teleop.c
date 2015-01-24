#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ultrasonic,     sensorSONAR)
#pragma config(Motor,  mtr_S1_C2_1,     mRight2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     mRight1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_1,     mLeft1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     mLeft2,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_3,    tubeHook1,            tServoStandard, reversed)
#pragma config(Servo,  srvo_S1_C3_4,    tubeHook2,            tServoStandard, reversed)

//*!!Codez automagically venerated by 'ROWBOAT SEA' conflagration lizard               !!*//

#include "drivers/teleoputils.h"

bool useTankDrive = false;

void invokeButton(int button, bool pressed) {
	switch(button) {
		case BUTTON_B:
			if(pressed)
			{
				if(servo[tubeHook1] != HOOK1_HOOKREST)
				{
					servo[tubeHook1] = HOOK1_HOOKREST;
				}
				else
				{
					servo[tubeHook1] = HOOK1_HOOKDOWN;
				}
			} else {} break;
		case BUTTON_X:
			if(pressed)
			{
				if(servo[tubeHook2] != HOOK2_HOOKREST)
				{
					servo[tubeHook2] = HOOK2_HOOKREST;
				}
				else
				{
					servo[tubeHook2] = HOOK2_HOOKDOWN;
				}
			} else {} break;
		case BUTTON_Y:
			if(pressed) {retractHooks();} else {} break;
		//case BUTTON_RB:
		//	if(pressed) {motor[mSlide2] = 58;} else {motor[mSlide2] = 0;} break;
		//case BUTTON_BA:
		//	if(pressed) {motor[mSlide1] = 35;} else {motor[mSlide1] = 0;} break;
		//case BUTTON_LB:
		//	if(pressed) {motor[mSlide1] = -55;} else {motor[mSlide1] = 0;} break;
		//case BUTTON_ST:
		//	if(pressed) {motor[mSlide2] = -35;} else {motor[mSlide2] = 0;} break;
		//case BUTTON_A:
		//	if(pressed)
		//		{
		//			if(motor[mChain] != 50 * CHAINSPEEDSCALAR)
		//			{
		//				motor[mChain] = 50 * CHAINSPEEDSCALAR;
		//			}
		//			else
		//			{
		//				motor[mChain] = 0;
		//			}
		//		} else {} break;

		//case BUTTON_Y:
		//	if(pressed)
		//		{
		//			if(motor[mChain] != 100)
		//			{
		//				motor[mChain] = 100;
		//			}
		//			else
		//			{
		//				motor[mChain] = 0;
		//			}
		//		} else {} break;

		case BUTTON_L3:
			if(pressed)
			{
				useTankDrive = !useTankDrive;
			}
			break;
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
  //nMotorEncoder[mSlide1] = 0;
  //nMotorEncoder[mSlide2] = 0;

  int gateMotorDir = 1;
 	while(true) {
		getJoystickSettings(joystick);
		checkJoystickButtons();


		writeDebugStreamLine("rightEncoder: %d, leftEncoder: %d", rightEncoder, leftEncoder);

		if(joystick.joy1_TopHat == -1)
		{
			if(useTankDrive)
			{
				setRightMotors(powscl(-1.0*JOY_Y2));
				setLeftMotors(powscl(-1.0*JOY_Y1));
			}
			else
			{
				joyYScaled = powscl(-1.0*JOY_Y1);

				joyXScaled = powscl(JOY_X1);

				setRightMotors(clamp_int(joyYScaled +joyXScaled, -100, 100));
				setLeftMotors(clamp_int(joyYScaled - joyXScaled, -100, 100));
			}
		}
		else
		{
			setRightMotors(getRightPowTopHat(joystick.joy1_TopHat));
			setLeftMotors(getLeftPowTopHat(joystick.joy1_TopHat));
		}
		//if(abs(joystick.joy1_y2) > 15.0)
		//{
		//	motor[mChain] = (powscl(joystick.joy1_y2) * CHAINSPEEDSCALAR);
		//}
		//else
		//{
		//	motor[mChain] = 0;
		//}

		//if(abs(joystick.joy1_x2) > 15.0)
		//{
		//	motor[motorA] = (joystick.joy1_x2/128.0) * 20;
		//}
		//else
		//{
		//	motor[motorA] = 0;
		//}
	}
}
