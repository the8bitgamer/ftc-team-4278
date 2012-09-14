#include "JoystickDriver.c"
#include "JoystickReadWrite.c"
/*
task main()
{
  recordInit("testFileOut.txt");
  while(true)
  {
    getJoystickSettings(joystick);
    recordJoystickValue((byte)joystick.joy1_y1);
    recordJoystickValue((byte)joystick.joy1_x1);
    recordJoystickValue((byte)joystick.joy1_y2);
    recordJoystickValue((int)joystick.joy1_Buttons);
    recordJoystickValue((byte)joystick.joy1_TopHat);
    motor[motorA] = joystick.joy1_y1;
    wait1Msec(10);
    //if(nIoResult == ioRsltEofExpected) nxtDisplayTextLine(3, "NOOOO");
    nxtDisplayTextLine(3, ""+(byte)joystick.joy1_y1);
    nxtDisplayTextLine(4, ""+(byte)joystick.joy1_x1);
  }
}
*/
task main()
{
  readInit("testFileOut.txt");
  while(true)
  {
    joystick.joy1_y1 = readJoystickValue((byte)1)-48;
    motor[motorA] = joystick.joy1_y1;
    joystick.joy1_x1 = readJoystickValue((byte)1)-48;
    joystick.joy1_y2 = readJoystickValue((byte)1)-48;
    joystick.joy1_Buttons = readJoystickValue((int)1);
    joystick.joy1_TopHat = readJoystickValue((byte)1);
    joystick.joy1_TopHat -= 48;
    nxtDisplayTextLine(3, ""+joystick.joy1_y1);
    nxtDisplayTextLine(4, ""+joystick.joy1_x1);
    nxtDisplayTextLine(5, ""+joystick.joy1_y2);
    nxtDisplayTextLine(6, ""+joystick.joy1_Buttons);
    nxtDisplayTextLine(7, ""+joystick.joy1_TopHat);
    wait1Msec(10);
  }
}
