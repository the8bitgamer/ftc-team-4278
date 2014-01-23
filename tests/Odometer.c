#define WHEELBASE 12
#define ENCTODIST 1440

float xPos, yPos, theta;

void encPos() {
	int lEnc, rEnc, dl, dr, lLEnc, lREnc;
	float lIn, rIn, dist;
	while(true) {
		lEnc = nMotorEncoder[lWheels];
		rEnc = nMotorEncoder[rWheels];

		dl = lEnc - lLEnc; 
		dr = rEnc - lREnc;

		lIn = (float)dl/ENCTODIST;
		rIn = (float)dr/ENCTODIST;

		dist = 0.5 * (lIn + rIn);

		theta += (rIn - lIn)/WHEELBASE;
		xPos  += (dist * cos(theta));
		yPos  += (dist * sin(theta));

		wait1Msec(50);
	}
}