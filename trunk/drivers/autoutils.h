#ifndef __AUTODRIVER__
#define __AUTODRIVER__
#include "sharedutils.h"

#define AOPINIT 0
#define AOPMOVE 1
//Define additional function statements

bool badGyroRange(float min, float max) {/*Check if gryo angles are within a good range*/}
bool badAcclRange(float min, float max) {/*Check if accel position is within a good range*/}
bool collisionCheck() {/*Check if we've collided with something => erroneous gyro, accel*/}

void lockdownRobot() {
	setLeftMotors(0);
	setRightMotors(0);
	setArmMotors(0);
	setSpinMotor(0);
	while(true) wait1Msec(5);
}

int operatingIndex = AOPINIT;
void setOperIndex(int action) {operatingIndex = action; wait1Msec(250);}

#define WHEELRAD 4.0
int getEncoderByInches(float inches) {return floor((1440)*(inches)/(2.0*PI*WHEELRAD));}

#endif //__AUTODRIVER__
