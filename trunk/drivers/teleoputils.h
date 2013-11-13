#ifndef __TELEOPDRIVER__
#define __TELEOPDRIVER__

#include "sharedutils.h"
#include "JoystickDriver4278.c"

#ifndef THRESHOLD
#define THRESHOLD 10
#endif

//Controller 1 - Left Joystick - Linear
#define joy1x1 (abs(joystick.joy1_x1) > THRESHOLD?joystick.joy1_x1:0)
#define joy1y1 (abs(joystick.joy1_y1) > THRESHOLD?joystick.joy1_y1:0)

//Controller 2 - Left Joystick - Linear
#define joy2x1 (abs(joystick.joy2_x1) > THRESHOLD?joystick.joy2_x1:0)
#define joy2x1 (abs(joystick.joy2_x1) > THRESHOLD?joystick.joy2_x1:0)

int expJoy(int joy){
	if(joy>0) {
		return exp(map((float)joy, THRESHOLD, 128.0, 2.3025851, 4.60517));
	} else if(joy<0){
		return -1 * exp((map((float)(-1*joy), THRESHOLD, 127.0, 2.3025851, 4.60517)));
	} else{
		return 0;
	}	
}

//Controller 1 - Left Joystick - Exponential
#define joy1x1exp (expJoy(joy1x1))
#define joy1y1exp (expJoy(joy1y1))

//Controller 2 - Left Josytick - Exponential
#define joy2x1exp (expJoy(joy2x1))
#define joy2x1exp (expJoy(joy2x1))

//TODO: Not sure if this actually is how it works
void tankDrive(int x, int y){
	motorLeft(y+x);
	motorRight(y-x);
}

//TODO: Map consistent macros for button-checking functions on each type (XBOX not necessary)
#ifdef NEWLOG
//Controller 1
#define joy1X joy1Btn()
#define joy1Y joy1Btn()
#define joy1B joy1Btn()
#define joy1A joy1Btn()

#define joy1RightBumper joy1Btn()
#define joy1LeftBumper joy1Btn()

#define joy1TopHat joystick.joy1_TopHat

//Controller 2
#define joy2X joy2Btn()
#define joy2Y joy2Btn()
#define joy2B joy2Btn()
#define joy2A joy2Btn()

#define joy2RightBumper joy2Btn()
#define joy2LeftBumper joy2Btn()

#define joy2TopHat joystick.joy2_TopHat

#elif OLDLOG
//Controller 1
#define joy1X joy1Btn()
#define joy1Y joy1Btn()
#define joy1B joy1Btn()
#define joy1A joy1Btn()

#define joy1RightBumper joy1Btn()
#define joy1LeftBumper joy1Btn()

#define joy1TopHat joystick.joy1_TopHat

//Controller 2
#define joy2X joy2Btn()
#define joy2Y joy2Btn()
#define joy2B joy2Btn()
#define joy2A joy2Btn()

#define joy2RightBumper joy2Btn()
#define joy2LeftBumper joy2Btn()

#define joy2TopHat joystick.joy2_TopHat
#elif XBOX
//We could take the time to do this, or just not.
#endif

#endif