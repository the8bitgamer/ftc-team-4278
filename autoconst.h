#ifndef __CALIBRATED__
//#error "You must specify __OPTIMAL__ or __CALIBRATED__."
#warning "You have not specified __CALIBRATED__; using __OPTIMAL__ encoder values."
#endif

#ifdef __CALIBRATED__
	#define LC1_ENC  691
	#define LC2_ENC 1900
	#define LC3_ENC 4000
	#define LC4_ENC 5264

	#define RC1_ENC 1003
	#define RC2_ENC 2266
	#define RC3_ENC 4935
	#define RC4_ENC 5797
#else
	#define LC1_ENC  691
	#define LC2_ENC 1900
	#define LC3_ENC 4000
	#define LC4_ENC 5264

	#define RC1_ENC 1003
	#define RC2_ENC 2266
	#define RC3_ENC 4935
	#define RC4_ENC 5797
#endif

#define LC12_THRESH ((LC1_ENC+LC2_ENC)/2)
#define LC23_THRESH ((LC2_ENC+LC3_ENC)/2)
#define LC34_THRESH ((LC3_ENC+LC4_ENC)/2)

#define RC12_THRESH ((RC1_ENC+RC2_ENC)/2)
#define RC23_THRESH ((RC2_ENC+RC3_ENC)/2)
#define RC34_THRESH ((RC3_ENC+RC4_ENC)/2)
