#ifndef __AUTOCONST__
#define __AUTOCONST__

#define NXT_LOW_BAT  8100
#define EXT_LOW_BAT 12800

#ifndef __OLD_CONST__
	#define C1_ENC  100 //Optimal 100
	#define C2_ENC  982 //Optimal 982
	#define C3_ENC 3160 //Optimal 3160
	#define C4_ENC 4306 //Optimal 4306

	#define BRIDGE_ENC 5853
	#define IR_REALIGN 1.0

	#define C12_THRESH ((C1_ENC+C2_ENC)/2)
	#define C23_THRESH ((C2_ENC+C3_ENC)/2)
	#define C34_THRESH ((C3_ENC+C4_ENC)/2)

	int getClosestCrate(int encDist) {
		int minD = abs(encDist - C1_ENC); int crate = 1;
		if(abs(encDist - C2_ENC) < minD) crate = 2;
		if(abs(encDist - C3_ENC) < minD) crate = 3;
		if(abs(encDist - C4_ENC) < minD) crate = 4;
		return crate;
	}
#else
	#define LC1_ENC  691
	#define LC2_ENC 1900
	#define LC3_ENC 4000
	#define LC4_ENC 5264

	#define RC1_ENC 1003
	#define RC2_ENC 2266
	#define RC3_ENC 4935
	#define RC4_ENC 5797

	#define LC12_THRESH ((LC1_ENC+LC2_ENC)/2)
	#define LC23_THRESH ((LC2_ENC+LC3_ENC)/2)
	#define LC34_THRESH ((LC3_ENC+LC4_ENC)/2)

	#define RC12_THRESH ((RC1_ENC+RC2_ENC)/2)
	#define RC23_THRESH ((RC2_ENC+RC3_ENC)/2)
	#define RC34_THRESH ((RC3_ENC+RC4_ENC)/2)
#endif

#endif // __AUTOCONST__
