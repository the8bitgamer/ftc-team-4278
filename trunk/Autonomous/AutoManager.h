#define autoVNull (-1)
#define autoVF1 1
#define autoVF2 2
#define autoVF3 3
#define autoVD1 4
#define autoVD2 5
#define autoVD3 6
#define autoVB1 7
#define autoVB2 8
#define autoVB3 9
#define autoFront 1
#define autoDef 2
#define autoBack 3

int currentIns = 1;
int currentAuton = 0;

void nextInstruction() {
	currentIns++;
	stopMotors();
	resetAccelGyroData();
	wait1Msec(250);
	ClearTimer(T2);
}

bool autoF1() {
	switch(currentIns) {
		case 1: return moveToWhite(0, 1, 0.8);
		case 2: if(time1[T2] > 1250) return true; return moveToPos(-0.23, 0, 0.5);
		case 3: return moveToRot(22);
		case 4: if(time1[T2] > 2000) return true; return moveToPos(0, 1, 0.8);
		case 5:
			motor[motorAmrL] = -30;
			motor[motorAmrR] = -30;
			wait1Msec(600);
			motor[motorAmrL] = 0;
			motor[motorAmrR] = 0;
			return true;
		case 6: if(time1[T2] > 2750) return true; return moveToPos(0, -2, .6);
		default:
			return false;
	}
}

bool autoF2() {
	switch(currentIns) {
		case 1: return moveToWhite(0, 1, 0.8);
		case 2: return moveToRot(42);
		case 3: if(time1[T2] > 450) return true; return moveToPos(0, .1, 1);
		case 4:
			motor[motorAmrL] = -30;
			motor[motorAmrR] = -30;
			wait1Msec(475);
			motor[motorAmrL] = 0;
			motor[motorAmrR] = 0;
			return true;
		case 5: if(time1[T2] > 2750) return true; return moveToPos(0, -2, .6);
		default: return false;
	}
}

bool autoF3() {
	switch(currentIns) {
		case 1: return moveToWhite(0, 1, 0.8);
		case 2: if(time1[T2] > 900) return true; return moveToPos(0, -.5, 0.5);
		case 3: return moveToRot(66);
		case 4: if(time1[T2] > 1400) return true; return moveToPos(0,.45,1);
		case 5:
			motor[motorAmrL] = -30;
			motor[motorAmrR] = -30;
			wait1Msec(475);
			motor[motorAmrL] = 0;
			motor[motorAmrR] = 0;
			return true;
		case 6: if(time1[T2] > 2750) return true; return moveToPos(0, -2, .6);
		default:
			return false;
	}
	return false;
}

bool autoD1() {
	switch(currentIns) {
		case 1:
			return false;
		default:
			return false;
	}
}

bool autoD2() {
	switch(currentIns) {
		case 1:
			return false;
		default:
			return false;
	}
}

bool autoD3() {
	switch(currentIns) {
		case 1:
			return false;
		default:
			return false;
	}
}

bool autoB1() {
	switch(currentIns) {
		case 1:
			return false;
		default:
			return false;
	}
}

bool autoB2() {
	switch(currentIns) {
		case 1:
			return false;
		default:
			return false;
	}
}

bool autoB3() {
	switch(currentIns) {
		case 1:
			return false;
		default:
			return false;
	}
}

void AutonomousManager() {
	switch(currentAuton) {
		case autoVNull: break;
		case autoVF1: if(autoF1()) nextInstruction(); break;
		case autoVF2: if(autoF2()) nextInstruction(); break;
		case autoVF3: if(autoF3()) nextInstruction(); break;
		case autoVD1: if(autoD1()) nextInstruction(); break;
		case autoVD2: if(autoD2()) nextInstruction(); break;
		case autoVD3: if(autoD3()) nextInstruction(); break;
		case autoVB1: if(autoB1()) nextInstruction(); break;
		case autoVB2: if(autoB2()) nextInstruction(); break;
		case autoVB3: if(autoB3()) nextInstruction(); break;
	}
}
