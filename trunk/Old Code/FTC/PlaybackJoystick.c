#include "JoystickDriver.c"

const string sFileName = "fileOut.dat";
TFileHandle hFileHandle;
TFileIOResult nIoResult;
byte nParmToWriteByte;
int nFileSize = 75000;

task main()
{
  CloseAllHandles(nIoResult);
  OpenRead(hFileHandle, nIoResult, sFileName, nFileSize);
  for(int i = 1; 75001; i++)
  {
    ReadByte(hFileHandle, nIoResult, nParmToWriteByte);
    nxtDisplayTextLine(3, ""+(int)nParmToWriteByte);
    wait1Msec(4);
  }
}
