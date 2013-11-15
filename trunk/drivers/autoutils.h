#ifndef __AUTODRIVER__
#define __AUTODRIVER__
#include "sharedutils.h"

#define AOPINIT 0
#define AOPMOVE 1
//Define additional function statements

bool badGyroRange(float min, float max) {/*Check if gryo angles are within a good range*/}
bool badAcclRange(float min, float max) {/*Check if accel position is within a good range*/}
bool collisionCheck() {/*Check if we've collided with something => erroneous gyro, accel*/}

void lockdownRobot() {/*Turn off motors, movement, end program*/}

int operatingIndex = AOPINIT;
void setAutoAction(int action) {operatingIndex = action; wait1Msec(250);}

#endif
