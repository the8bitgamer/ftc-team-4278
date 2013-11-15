#ifndef __SHAREDUTILSH__
#define __SHAREDUTILSH__

//Distance Macros - Every function dealing with distance should be
//written in terms of the imperial inch
#define INCH 1.0
#define CM 0.393701
#define MM 39.3701
#define YARD 36
#define FOOT 12
#define METER 39.3701

#define FLOORMAT (2.0 * FOOT)
//Distance from corner to center of pendulum
#define CORNERtoPEND (5.6568542 * FOOT)

#define WHEEL (4.0 * INCH * PI)
#define ROTPERMAT (FLOORMAT / WHEEL)

float linearScale(float x, float in_min, float in_max, float out_min, float out_max) {return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;}

#define motorLeft(x) motor[motorL1] = x; motor[motorL2] = x
#define motorRight(x) motor[motorR1] = x; motor[motorR2] = x

#endif
