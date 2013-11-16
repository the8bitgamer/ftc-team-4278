#ifndef __SHAREDUTILSH__
#define __SHAREDUTILSH__

#define setLeftMotors(x)  {motor[mLeft1]  = x; motor[mLeft2]  = x;}
#define setRightMotors(x) {motor[mRight1] = x; motor[mRight2] = x;}
#define setArmMotors(x) {motor[mArm1] = x; motor[mArm2] = -x;}

//Distance Macros - Every function dealing with distance should be
//written in terms of the imperial inch
#define INCH 1.0
#define CM 0.393701
#define MM 39.3701
#define YARD 36.0
#define FOOT 12.0
#define METER 39.3701

#define FLOORMAT (2.0 * FOOT)
//Distance from corner to center of pendulum
#define CORNERtoPEND (5.6568542 * FOOT)

#define WHEEL (4.0 * INCH * PI)
#define ROTPERMAT (FLOORMAT / WHEEL)

float linearScale(float x, float in_min, float in_max, float out_min, float out_max) {return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;}
void displayDiagnostics() {
	if(externalBatteryAvg < 0)
  	nxtDisplayTextLine(3, "Ext Batt: OFF");
 	else
  	nxtDisplayTextLine(3, "Ext Batt:%4.1f V", externalBatteryAvg / (float) 1000);
  nxtDisplayTextLine(4, "NXT Batt:%4.1f V", nAvgBatteryLevel / (float) 1000);
}

#endif
