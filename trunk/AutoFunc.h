
int targetFunc = 0;
int targetFuncState = 0;

void setTargetFunc(int tgt) {
	targetFunc = tgt;
	targetFuncState = 0;
}

void entrySelection() {}
void irSeek01() {}
void irSeek02() {}
void scoreIRBlock() {}
void irSeekBack() {}
void scoreBlock() {}
void moveBridge() {}

void oaReverse() {}
void oaSpeedCalc() {}
void oaScoreNearest() {}
void oaNearestBridge() {}

void obForward() {}
void obSpeedCalc() {}
void obScoreNearest() {}
void obNearestBridge() {}

void checkCollision() {}
void checkErrorBound() {}
void checkObjectAhead() {}
void checkObjectBehind() {}

#define ENTRY    00
#define IRSEEK01 01
#define IRSEEK02 02
#define SCOREIR  03
#define REVSEEK  04
#define SCOREERR 05
#define BRIDGE   06

#define COLLIDE  07
#define ERRBOUND 08

#define OA_REVER 09
#define OA_SPEED 10
#define OA_SCORE 11
#define OA_BRIDG 12

#define OB_FORWD 13
#define OB_SPEED 14
#define OB_SCORE 15
#define OB_BRIDG 16
