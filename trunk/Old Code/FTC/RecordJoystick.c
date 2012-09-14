#include "JoystickDriver.c"

int joyBtn(int btn) {
  return (((int)(joystick.joy1_Buttons << btn)%2 > 0);
}

const string sFileName = "fileOut.dat";
TFileHandle hFileHandle;
TFileIOResult nIoResult;
byte nParmToWriteByte;
int nFileSize = 75000;

task main()
{
  CloseAllHandles(nIoResult);
  Delete(sFileName, nIoResult);
  OpenWrite(hFileHandle, nIoResult, sFileName, nFileSize);
  int i = 0;
  bool enterHasBeenPressed = false;
  while(true)
  {
    getJoystickSettings(joystick);
    nParmToWriteByte = abs(joystick.joy1_y1);
    if(nNxtButtonPressed == 3) enterHasBeenPressed = true;
    if(enterHasBeenPressed) WriteByte(hFileHandle, nIoResult, nParmToWriteByte);
    //bOverrideJoystickDisabling = true;
    nxtDisplayTextLine(3, ""+joystick.joy1_y1);
    wait1Msec(4);
    if(i < 75001)
    {
      i++;
      nxtDisplayTextLine(5, ""+i);
    }
  }
}
