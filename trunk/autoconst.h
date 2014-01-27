#ifndef __AUTOCONST__
#define __AUTOCONST__

#define NXT_LOW_BAT  8100
#define EXT_LOW_BAT 12800

#ifndef __OLD_CONST__
	#define C1_ENC  691
	#define C2_ENC 1900
	#define C3_ENC 4000
	#define C4_ENC 5264

	#define BRIDGE_ENC 6200

	#define C12_THRESH ((C1_ENC+C2_ENC)/2)
	#define C23_THRESH ((C2_ENC+C3_ENC)/2)
	#define C34_THRESH ((C3_ENC+C4_ENC)/2)
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
