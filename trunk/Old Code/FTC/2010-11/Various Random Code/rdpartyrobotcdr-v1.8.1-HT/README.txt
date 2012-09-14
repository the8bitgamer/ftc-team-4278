/*
 * $Id: README.txt 40 2011-01-03 09:37:09Z xander $
 */

-= Note =-
These drivers are for RobotC 2.00 and higher and are part of the
version 1.8 of the 3rd Party RobotC Drivers suite.

-= Changes in this version =-
* common.h: added check for sensor type for all I2C calls.  To disable this check, please
  refer to the source code.
* DGPS: added missing DGPSreadDistToDestination(tSensors link) function
* HT Angle Sensor: added Sensor MUX support
* HT Compass: enhanced HTMCreadRelativeHeading() function
* Lego US: Added lots of new functions:
int USreadDist(tSensors link);
bool USreadDistances(tSensors link, tByteArray &distances);
bool _USsendCmd(tSensors link, ubyte command);
bool USsetSingleMode(tSensors link);
bool USsetContinuousMode(tSensors link);
bool USsetOff(tSensors link);
bool USsetEventCapture(tSensors link);
bool USreset(tSensors link);
* MS Dist: Commands can be sent to arbitrary I2C addresses now with optional argument
* MS HID: Commands can be sent to arbitrary I2C addresses now with optional argument
* MS NumPad: Added MSNPscanKeys()
* MS NXT Cam: Removed printDebugLine from driver

-= API Documentation =-
The complete API documentation can be found in the html folder.
Just point your browser at the index.html file.


-= Downloads and support =-
These drivers can also be downloaded from:
http://sourceforge.net/projects/rdpartyrobotcdr/

The documentation is hosted here:
http://rdpartyrobotcdr.sourceforge.net/documentation/index.html

For support questions, please use the RobotC 3rd party sensors forum:
http://www.robotc.net/forums/viewforum.php?f=41

Thanks,
Xander Soldaat (mightor@gmail.com)

/*
 * $Id: README.txt 40 2011-01-03 09:37:09Z xander $
 */