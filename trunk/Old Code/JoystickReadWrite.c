#ifndef getJoystickSettings
#include "JoystickDriver.c"
#endif

string recordFileName = "fileOut.dat";
TFileHandle hFileHandle;
TFileIOResult nIoResult;

byte nParmToWriteByte;
long nParmToWriteLong;
short nParmToWriteShort;
byte nParmToReadByte;
long nParmToReadLong;
short nParmToReadShort;
int nFileSize = 150000; //Modify as necessary for 30s

void recordInit(string sFileName)
{
  CloseAllHandles(nIoResult);
  Delete(sFileName, nIoResult);
  OpenWrite(hFileHandle, nIoResult, sFileName, nFileSize);
}

void recordJoystickValue(byte value)
{
  nParmToWriteByte = value;
  WriteByte(hFileHandle, nIoResult, nParmToWriteByte);
}

void recordJoystickValue(long value)
{
  nParmToWriteLong = value;
  WriteLong(hFileHandle, nIoResult, nParmToWriteLong);
}

void recordJoystickValue(short value)
{
  nParmToWriteShort = value;
  WriteShort(hFileHandle, nIoResult, nParmToWriteShort);
}
//////////////////////////////////////////////////////////////////////////////////
void readInit(string fileName)
{
  CloseAllHandles(nIoResult);
  OpenRead(hFileHandle, nIoResult, fileName, nFileSize);
}

byte readJoystickValue(byte i)
{
  ReadByte(hFileHandle, nIoResult, nParmToReadByte);
  //if(abs(nParmToReadByte) == 128) nParmToReadByte = nParmToReadByte * -1;
  char tempChar = nParmToReadByte + '0';
  nxtDisplayTextLine(2, ""+nParmToReadByte);
  return tempChar;
}

long readJoystickValue(long i)
{
  ReadLong(hFileHandle, nIoResult, nParmToReadLong);
  return nParmToReadLong;
}

short readJoystickValue(short i)
{
  ReadShort(hFileHandle,  nIoResult, nParmToReadShort);
  return nParmToReadShort;
}
