#pragma config(Sensor, S1,     HTMC,                sensorLowSpeed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: HTMC-test1.c 20 2009-12-08 22:59:13Z xander $
 */

/**
 * HTMC-driver.h provides an API for the HiTechnic Compass Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 25 November 2009
 * version 0.2
 */

#include "drivers/HTMC-driver.h"

task main () {
  int _target = 0;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Compass");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayTextLine(5, "Press enter");
  nxtDisplayTextLine(6, "to set target");

  wait1Msec(2000);
  eraseDisplay();
  time1[T1] = 0;
  while(true) {
    // Reset the target no more than once a second
    // This also helps with debouncing the [enter] button.
    if (time1[T1] > 1000) {
      eraseDisplay();
      nxtDisplayTextLine(1, "Changing");
      nxtDisplayTextLine(2, "target");
      wait1Msec(500);
      // Set the current heading as the value for the offset to be used as the
      // new zero-point for the relative heading returned by
      // HTMCreadRelativeHeading()
      _target = HTMCsetTarget(HTMC);
      PlaySound(soundBlip);
      while(bSoundActive);
      time1[T1] = 0;
    }

    // Get the true heading and relative heading from the sensor and
    // display them on the screen.
    while(nNxtButtonPressed != kEnterButton) {
      eraseDisplay();
      nxtDisplayTextLine(1, "Reading");
      nxtDisplayTextLine(2, "Target: %4d", _target);
      nxtDisplayTextLine(4, "Abs:   %4d", HTMCreadHeading(HTMC));
      nxtDisplayTextLine(5, "Rel:   %4d", HTMCreadRelativeHeading(HTMC));
      nxtDisplayTextLine(6, "Press enter");
      nxtDisplayTextLine(7, "to set target");
      wait1Msec(100);
    }
  }
}

/*
 * $Id: HTMC-test1.c 20 2009-12-08 22:59:13Z xander $
 */
