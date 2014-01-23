#pragma config(Sensor, S4,     HTSPB,                sensorI2CCustom9V)

#include "drivers/wiringnxt.h"

task main()
{
	HTSPBsetupIO(HTSPB, 0xFF);
	for(;;){
		nxtDisplayTextLine(3, "A3: %d", analogRead(A3));
	}

}
