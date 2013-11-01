#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)

#include "drivers/WiringNXT.h"

#define D 1
#define doatest for(short i=0;i<D;i++)

float xAcc =0;
long sum =0;

task main() {
	HTSPBsetupIO(HTSPB, 0xFF);
	while(true) {
		doatest{
			sum += HTSPBreadADC(HTSPB,0,8);
		}
		xAcc = sum/D;
		sum =0;
		nxtDisplayTextLine(3, "A0: %d", xAcc);
	}
}
