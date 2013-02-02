#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-colour-v2.h"

#define motorArmR motor[motorAmrR]
#define motorArmL motor[motorAmrL]

int armTargetLevel = -1;
const tMUXSensor colorSnsArm = msensor_S1_4;

void RunArmState() {
	int _r, _b, _g;
	HTCS2readRGB(colorSnsArm, _r, _g, _b);
	switch(armTargetLevel) {
		case 1:
			if(_b < 120 && _b > 80 && _g < 80 && _r < 40) {armTargetLevel = -1; break;}
			motorArmR = 60; motorArmL = 60;
			break;
		case 2:
			if(_g > 60 && _r < 30 && _b < 60) {armTargetLevel = -1; break;}
			motorArmR = 60; motorArmL = 60;
			break;
		case 3:
			if(_r > 110 && _g < 50 && _b < 50) {armTargetLevel = -1; break;}
			motorArmR = 60; motorArmL = 60;
			break;
		case -1:
			motorArmL = 0;
			motorArmR = 0;
		default:
			motorArmR = 0;
			motorArmL = 0;
	}
}
