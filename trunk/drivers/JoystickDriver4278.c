#ifndef __JDRIVER4278__
#define __JDRIVER4278__

#pragma autoStartTasks
#pragma systemFile

typedef struct {
  bool    UserMode;
  bool    StopPgm;

  short   joy1_x1;
  short   joy1_y1;
  short   joy1_x2;
  short   joy1_y2;
  short   joy1_Buttons;
  short   joy1_TopHat;
} TJoystick;
TJoystick joystick;

#if defined(hasJoystickMessageOpcodes)
intrinsic void getJoystickSettings(TJoystick &joystick)
asm(opcdSystemFunctions, byte(sysFuncGetJoysticks),
variableRefRAM(joystick));
#endif

#define getJoystickSettings(joystick) 	memcpy(joystick, joystickCopy, sizeof(joystick))
#define NOMSG_LIMIT 500

bool joy1Btn(int btn) {return ((joystick.joy1_Buttons & (1 << btn)) != 0);}

const TMailboxIDs kJoystickQueueID = mailbox1;
TJoystick joystickCopy;  // Internal buffer to hold the last received message from the PC. Do not use

bool bDisconnected = false;
long nNoMessageCounter = 0;

task readMsgFromPC() {
  bool bMsgFound;

  TFileIOResult nBTCmdRdErrorStatus;
  const int kMaxSizeOfMessage = 18;
  sbyte tempBuffer[kMaxSizeOfMessage];

  joystickCopy.UserMode  = false;
  joystickCopy.StopPgm   = true;

  joystickCopy.joy1_x1 = 0;
  joystickCopy.joy1_y1 = 0;
  joystickCopy.joy1_x2 = 0;
  joystickCopy.joy1_y2 = 0;
  joystickCopy.joy1_Buttons = 0;
  joystickCopy.joy1_TopHat = -1;

  bool bTempUserMode, bTempStopPgm;

  while(true) {
    bMsgFound = false;
    bDisconnected = false;
    while(true) {
      int nSizeOfMessage;
      nSizeOfMessage = cCmdMessageGetSize(kJoystickQueueID);

      if(nSizeOfMessage <= 0) {
        if(!bMsgFound) {
          if(nNoMessageCounter > NOMSG_LIMIT) {
            hogCPU();
            bTempUserMode = joystickCopy.UserMode;
            bTempStopPgm = joystickCopy.StopPgm;

            memset(joystickCopy, 0, sizeof(joystickCopy));

            joystickCopy.UserMode = bTempUserMode;
            joystickCopy.StopPgm = bTempStopPgm;
            joystickCopy.joy1_TopHat = -1;
            bDisconnected = true;
            releaseCPU();
          }
          wait1Msec(4);
          nNoMessageCounter++;
          continue;
        } else {
          bDisconnected = false;
          nNoMessageCounter = 0;
          break;
        }
      }

      if(nSizeOfMessage > sizeof(tempBuffer)) {nSizeOfMessage = sizeof(tempBuffer);}
      nBTCmdRdErrorStatus = cCmdMessageRead(&tempBuffer[0], nSizeOfMessage, kJoystickQueueID);
      nBTCmdRdErrorStatus = nBTCmdRdErrorStatus; //Get rid of info message

      bMsgFound = true;
    }

    hogCPU();
    joystickCopy.UserMode           = (bool)tempBuffer[1];
    joystickCopy.StopPgm            = (bool)tempBuffer[2];

    joystickCopy.joy1_x1            = tempBuffer[3];
    joystickCopy.joy1_y1            = tempBuffer[4];
    joystickCopy.joy1_x2            = tempBuffer[5];
    joystickCopy.joy1_y2            = tempBuffer[6];
    joystickCopy.joy1_Buttons       = (tempBuffer[7] & 0x00FF) | (tempBuffer[8] << 8);
    joystickCopy.joy1_TopHat        = tempBuffer[9];

    joystickCopy.joy1_y1            = -joystickCopy.joy1_y1;
    joystickCopy.joy1_y2            = -joystickCopy.joy1_y2;
    releaseCPU();
  }
}

#endif // __JDRIVER4278__
