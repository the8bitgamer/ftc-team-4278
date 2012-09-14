#pragma config(Sensor, S2, HTSMUX, sensorLowSpeed)

#include "drivers/HTGYRO-driver.h"

void MustHaveMoreError()
{
	while(true)
	{
		PlaySound(soundBeepBeep);
	}
}

task main()
{
	HTSMUXinit();
	HTSMUXscanPorts(HTSMUX);
	HTGYROstartCal(msensor_S2_1);

	if(HTGYROreadCal(msensor_S2_1) == 620) {PlaySound(soundLowBuzz);}
	if(HTGYROreadRot(msensor_S2_1) >= 5) {PlaySound(soundBeepBeep);}
	if(HTGYROreadRot(msensor_S2_1) <= -5) {PlaySound(soundFastUpwardTones);}
	if(HTGYROreadRot(msensor_S2_1) == 0) {PlaySound(soundDownwardTones);}
	wait10Msec(1000);
	if(HTSMUXreadAnalogue(msensor_S2_1) == 0 || HTSMUXreadAnalogue(msensor_S2_1) != HTGYROreadCal(msensor_S2_1)) {MustHaveMoreError();}
}
