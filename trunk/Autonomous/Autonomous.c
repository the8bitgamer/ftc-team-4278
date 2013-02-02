#define motorFR motor[motorA]
#define motorBR motor[motorA]
#define motorFL motor[motorA]
#define motorBL motor[motorA]

#define irThreshold 50
#define irMinThreshold 10

#define wheelSeparation 20.0
#define wheelSize 3.0

void motorsAll(int pw) {
	motorFR = pw;
	motorBR = pw;
	motorFL = pw;
	motorBL = pw;
}

void motorsLeft(int pw) {
	motorFL = pw;
	motorBL = pw;
}

void motorsRight(int pw) {
	motorFR = pw;
	motorBR = pw;
}

void moveRot(float degs) {
	float targetEnc = ((degs/(PI*wheelSeparation)) / (3.0*PI))*1440.0;
	motorsLeft(50*(degs>0?-1.0:1.0));
	motorsLeft(50*(degs>0?1.0:-1.0));
}

int readIRDir() {return 0;}

task main() {
	int maxIR = 0;
	while(readIRDir() < maxIR - irThreshold)
		motorsAll(75);
	motorsAll(0);
	while(readIRDir() < maxIR - irMinThreshold)
		motorsAll(-10);
	motorsAll(0);
	moveRot(90);
	ClearTimer(T1); while(time1(T1) < 550) motorsAll(25); motorsAll(0);
}
