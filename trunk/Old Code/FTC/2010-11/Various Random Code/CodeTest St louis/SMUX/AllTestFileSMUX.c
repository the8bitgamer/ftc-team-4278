#include "ShellSMUX.h"

/*
1: FLOAT Target distance in squares
2: FLOAT Target gyroscope (turning) value +/- 5 degrees
3: FLOAT Left wheel power from -100 to 100
4: FLOAT Right wheel power as percentage (in decimal format) of left wheel power. -1 to turn.
5: BOOL True if stop on color red
6: BOOL True if stop on color blue
7: BOOL True if stop on color white
8: BOOL True if stop on rolling goal (adjust sensetivity from within Shell)
9: FLOAT Number of squares to stop at if the conditions aren't fulfilled. 
*/

task main()
{
	initializeRobot(); //Shell handles multiplexor and gyros
}
