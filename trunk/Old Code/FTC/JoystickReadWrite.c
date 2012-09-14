#if !defined(getJoystickSettings)
#include "JoystickDriver.c"
#endif

const string recordFileName = "fileOut.dat";
TFileHandle hFileHandle;
TFileIOResult nIoResult;

byte nParmToWriteByte;
long nParmToWriteLong;
short nParmToWriteShort;
byte nParmToReadByte;
long nParmToReadLong;
short nParmToReadShort;
int nFileSize = 75000; //Modify as necessary for 30s

void recordInit()
{
  CloseAllHandles(nIoResult);
  Delete(sFileName, nIoResult);
  OpenWrite(hFileHandle, nIoResult, recordFileName, nFileSize);
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

byte readJoystickValue()
{
  ReadByte(hFileHandle, nIoResult, nParmToReadByte);
  char tempChar = nParmToReadByte + '0';

  return tempChar;
}

long readJoystickValue()
{
  ReadLong(hFileHandle, nIoResult, nParmToReadLong);
  return nParmToReadLong;
}

short readJoystickValue()
{
  ReadShort(hFileHandle, nIoResult, nParmToReadShort);
  return nParmToReadShort;
}
