#ifndef __AUTODRIVER__
#define __AUTODRIVER__
#include "sharedutils.h"

bool badGyroRange(float min, float max) {return false; /*Check if gryo angles are within a good range*/}
bool badAcclRange(float min, float max) {return false; /*Check if accel position is within a good range*/}
bool collisionCheck() {return false; /*Check if we've collided with something => erroneous gyro, accel*/}

void lockdownRobot() {
	setLeftMotors(0);
	setRightMotors(0);
	setArmMotors(0);
	setSpinMotor(0);
	while(true) wait1Msec(5);
}

int getEncoderByInches(float inches) {return floor((1440)*(inches)/WHEELCIRC);}

#endif //__AUTODRIVER__
