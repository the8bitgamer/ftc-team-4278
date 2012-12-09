#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-colour-v2.h"

#define motArmR motor[motorAmrR]
#define motArmL motor[motorAmrL]

int armLevel = -1;
const tMUXSensor colorSnsArm = msensor_S1_4;

void RunArmState() {
	int _ra, _ba, _ga;
	HTCS2readRGB(colorSnsArm, _ra, _ga, _ba);
	switch(armLevel) {
		case 1:
			if(_ba < 120 && _ba > 80 && _ga < 80 && _ra < 40) {armLevel = -1; break;}
			motArmR = 60; motArmL = 60;
			break;
		case 2:
			if(_ga > 60 && _ra < 30 && _ba < 60) {armLevel = -1; break;}
			motArmR = 60; motArmL = 60;
			break;
		case 3:
			if(_ra > 110 && _ga < 50 && _ba < 50) {armLevel = -1; break;}
			motArmR = 60; motArmL = 60;
			break;
		case -1:
			motArmL = 0;
			motArmR = 0;
		default:
			motArmR = 0;
			motArmL = 0;
	}
}
