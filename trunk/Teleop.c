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

#include "drivers/teleoputils.h"

void invokeButton(int button, bool pressed) {
	switch(button) {
		case JOY_X:  if(pressed) {lockArmMotors();} else {} break;
		case JOY_Y:  if(pressed) {unlockArmMotors();} else {} break;
		case JOY_A:  if(pressed) {} else {} break;
		case JOY_B:  if(pressed) {setSpinMotor(100);}  else {setSpinMotor(0);} break;
		case JOY_RB: if(pressed) {setArmMotors(100);}  else {setArmMotors(0);} break;
		case JOY_LB: if(pressed) {setArmMotors(-100);} else {setArmMotors(0);} break;
		case JOY_R3: if(pressed) {} else {} break;
		case JOY_L3: if(pressed) {} else {} break;
	}
}

//Kian: I think this is a better function to use because it 			
//checks all buttons at in the beginning if any have 
//changed, as opposed to checking each button individually 
//every time.
short butn = JOY_BTN;
void checkJoystickButtonsShort() {
	if(butn != JOY_BTN){
		for(int i = 7; i >= 0; i--) {
			if((butn>>i) ^ (JOY_BTN>>i) != 0) {
				invokeButton(i, ((butn & (1 << i)) == 0));
				butn ^= 1<<i;
			}
		}
	}
}

bool btn[8];
void checkJoystickButtons() {
	for(int i = 0; i < 8; i++) {
		if(joy1Btn(i) != btn[i]) {
			invokeButton(i, !btn[i]);
			btn[i] = !btn[i];
		}
	}
}

task main() {
	displayDiagnostics();
	invokeButton(JOY_Y, true);
	while(true) {
		getJoystickSettings(joystick);
		checkJoystickButtons();
		setLeftMotors(powscl(JOY_Y1)-powscl(JOY_X1)/1.75);
		setRightMotors(powscl(JOY_Y1)+powscl(JOY_X1)/1.75);
	}
}
