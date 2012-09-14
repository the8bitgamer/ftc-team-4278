
#include "JoystickDriver.c"

task main()
{
  eraseDisplay();
  getJoystickSettings(joystick);

    nxtDisplayTextLine(0, "" + joystick.joy1_y2 + ", " + joystick.joy1_x2);
    nxtDisplayTextLine(1, "" + joystick.joy1_y1 + ", " + joystick.joy1_x1);

  while(1 == 1) {}
}
