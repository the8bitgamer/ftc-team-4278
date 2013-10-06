#include "AutoFunc.h"

task main()
{
	while(true) {
		switch(targetFunc) {
			case ENTRY   : entrySelection();
			case IRSEEK01: irSeek01();
			case IRSEEK02: irSeek02();
			case SCOREIR : scoreIRBlock();
			case REVSEEK : irSeekBack();
			case SCOREERR: scoreBlock();
			case BRIDGE  : moveBridge();

			case COLLIDE : StopAllTasks();
			case ERRBOUND: StopAllTasks();

			case OA_REVER: oaReverse();
			case OA_SPEED: oaSpeedCalc();
			case OA_SCORE: oaScoreNearest();
			case OA_BRIDG: oaNearestBridge();

			case OB_FORWD: obForward();
			case OB_SPEED: obSpeedCalc();
			case OB_SCORE: obScoreNearest();
			case OB_BRIDG: obNearestBridge();
		}

		checkCollision();
		checkErrorBound();
		checkObjectAhead();
		checkObjectBehind();
	}
}
