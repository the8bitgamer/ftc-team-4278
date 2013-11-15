
#include "drivers/autoutils.h"

void initialize() {setAutoAction(AOPMOVE);}

task main() {
	bool error = false;
	while(!collisionCheck() && !error) {
		switch(operatingIndex) {
			case AOPINIT: initialize(); break;
			//Case calls for other autonomous functions

			default: lockdownRobot();
		}
	}
}
