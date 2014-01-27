#ifndef __JOSTICKDRIVERC4278__
#define __JOSTICKDRIVERC4278__

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

bool joy1Btn(int btn) {return ((joystick.joy1_Buttons & (1 << btn)) != 0);}

const TMailboxIDs kJoystickQueueID = mailbox1;
TJoystick joystickCopy;  // Internal buffer to hold the last received message from the PC. Do not use

long ntotalMessageCount = 0;

bool bDisconnected = false;
bool bOverrideJoystickDisabling = false;
long nNoMessageCounterLimit = 500;
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

      if (nSizeOfMessage <= 0) {
        if (!bMsgFound) {
          if (nNoMessageCounter > nNoMessageCounterLimit) {
            hogCPU();
            if (!bOverrideJoystickDisabling) {
              bTempUserMode = joystickCopy.UserMode;
              bTempStopPgm = joystickCopy.StopPgm;

              memset(joystickCopy, 0, sizeof(joystickCopy));

              joystickCopy.UserMode = bTempUserMode;
              joystickCopy.StopPgm = bTempStopPgm;
              joystickCopy.joy1_TopHat = -1;
            }
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
        // No more messages available and at least one message found. This is not essential but
        // useful to ensure that we're working with the latest message. We simply discard earlier
        // messages. This is useful because there could be many messages queued and we don't
        // want to work with stale data.
      }

      if(nSizeOfMessage > sizeof(tempBuffer)) {nSizeOfMessage = sizeof(tempBuffer);}
      nBTCmdRdErrorStatus = cCmdMessageRead(&tempBuffer[0], nSizeOfMessage, kJoystickQueueID);
      nBTCmdRdErrorStatus = nBTCmdRdErrorStatus; //Get rid of info message

      // Repeat loop until there are no more messages in the queue. We only want to process the
      // last message in the queue.
      bMsgFound = true;
    }

    hogCPU();   // grab CPU for duration of critical section

    ++ntotalMessageCount;

    joystickCopy.UserMode           = (bool)tempBuffer[1];
    joystickCopy.StopPgm            = (bool)tempBuffer[2];

    joystickCopy.joy1_x1            = tempBuffer[3];
    joystickCopy.joy1_y1            = tempBuffer[4];// Negate to "natural" position
    joystickCopy.joy1_x2            = tempBuffer[5];
    joystickCopy.joy1_y2            = tempBuffer[6];// Negate to "natural" position
    joystickCopy.joy1_Buttons       = (tempBuffer[7] & 0x00FF) | (tempBuffer[8] << 8);
    joystickCopy.joy1_TopHat        = tempBuffer[9];

    joystickCopy.joy1_y1            = -joystickCopy.joy1_y1; // Negate to "natural" position
    joystickCopy.joy1_y2            = -joystickCopy.joy1_y2; // Negate to "natural" position

    releaseCPU(); // end of critical section
  }
}

void waitForStart() {
  while(true) {
    getJoystickSettings(joystick);
    if(!joystick.StopPgm) break;
		//nxtDisplayTextLine(6, "Waiting for start...");
    //displayDiagnostics();
  }
}

#endif
