#ifndef CommonAnnodeSSD_h
#define CommonAnnodeSSD_h

#include "Arduino.h" 

#define ZERO B00001000
#define ONE B01101011
#define TWO B0100100
#define THREE B00100001
#define FOUR B01000011
#define FIVE B00010001
#define SIX B00010000
#define SEVEN B00101011
#define EIGHT B00000000
#define NINE B00000001
#define TEN B00010100
#define ERROR B00010100

class CommonAnnodeSSD{
	public:
		CommonAnnodeSSD(int * pins,int delay);
		void convertFourDigits(float num);
	private:
		void _setLED(byte set);
		void _mapDigit(int digit);
		void _setDigit(int pin, int number, boolean decimal);
		int _s1; int _s2; int _s3; int _s4; int _s5; int _s6; int _s7; int _s8; int _s9; int _s10; int _s11; int _s12;
		int _microsecondsDelay;
};

#endif