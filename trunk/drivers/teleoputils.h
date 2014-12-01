#ifndef __TELEOPDRIVER__
#define __TELEOPDRIVER__

#include "sharedutils.h"

//Allows threshold to be defined in teleop-file
#define THRESH 20.0
#define MINX   10.0
#define SLOPE   0.5
#define DISTA   0.6

//scale user from -128 to 127
float powscl(int xz) {
	float x = xz/128.0;

	return 100 * x;
}

//Controller 1 - Left Joystick - Linear
#define JOY_X1 (abs(joystick.joy1_x1) > THRESH ? joystick.joy1_x1 : 0)
#define JOY_Y1 (abs(joystick.joy1_y1) > THRESH ? -1.0*joystick.joy1_y1 : 0)

//Defines current button map layout
#define BUTTON_X 0
#define BUTTON_Y 3
#define BUTTON_B 2
#define BUTTON_A 1

#define BUTTON_RB 5
#define BUTTON_LB 4
#define BUTTON_LT 6
#define BUTTON_RT 7

#define BUTTON_R3 10
#define BUTTON_L3 11

#define BUTTON_ST 9
#define BUTTON_BA 8

#define JOY_BTN joystick.joy1_Buttons

int getLeftPowTopHat(int topHat) {
	if(topHat == 0) return 100;
	if(topHat == 6) return -100;
	if(topHat == 4) return -100;
	if(topHat == 2) return 100;
	return 0;
}

int getRightPowTopHat(int topHat) {
	//topHat--;
	if(topHat == 0) return 100;
	if(topHat == 6) return 100;
	if(topHat == 4) return -100;
	if(topHat == 2) return -100;
	return 0;
}

#endif //__TELEOPUTILS__
