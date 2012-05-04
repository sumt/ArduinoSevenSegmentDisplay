#include "Arduino.h" 
#include "CommonAnnodeSSD.h"

/*
constructor to set pins

@pins - an array of the arduino pins; 
		these will be mapped to the pins of the common annode ssd by the order that they are in the array; 
		for example pins 2 to 13 in the array will map to pins 1 to 12 on the ssd respectively
@delay - number of microseconds to delay the changing of an aruidno pin to low state from high state
*/
CommonAnnodeSSD::CommonAnnodeSSD(int *pins,int delay){
	_s1=pins[0];
	_s2=pins[1];
	_s3=pins[2];
	_s4=pins[3];
	_s5=pins[4];
	_s6=pins[5];
	_s7=pins[6];
	_s8=pins[7];
	_s9=pins[8];
	_s10=pins[9];
	_s11=pins[10];
	_s12=pins[11];
	_microsecondsDelay=delay;
	pinMode(_s1,OUTPUT);
	pinMode(_s2,OUTPUT);
	pinMode(_s3,OUTPUT);
	pinMode(_s4,OUTPUT);
	pinMode(_s5,OUTPUT);
	pinMode(_s6,OUTPUT);
	pinMode(_s7,OUTPUT);
	pinMode(_s8,OUTPUT);
	pinMode(_s9,OUTPUT);
	pinMode(_s10,OUTPUT);
	pinMode(_s11,OUTPUT);
	pinMode(_s12,OUTPUT); 
	digitalWrite(_s10,1);  
}

/*
helper function to set a digit; always called by mapDigit; common anode seven segment displays control digits using cathodes 2,3,6,8,9,11,12; 
cathodes are attached to pins on the arduino board and will light up on low state

@set - a byte in which the bits represent the high/low states; set each pin state, 1 or 0, using the bits read from set
*/
void CommonAnnodeSSD::_setLED(byte set){
  digitalWrite(_s2,bitRead(set,6));   
  digitalWrite(_s3,bitRead(set,5));
  digitalWrite(_s6,bitRead(set,4));   
  digitalWrite(_s8,bitRead(set,3));
  digitalWrite(_s9,bitRead(set,2));
  digitalWrite(_s11,bitRead(set,1));  
  digitalWrite(_s12,bitRead(set,0));  
}


/*
helper function that translates a digit represented by an int to a digit in the ssd; called by setDigit function 
@digit - the digit to map
*/
void CommonAnnodeSSD::_mapDigit(int digit){
  switch (digit){
    case 0:
		_setLED(ZERO);
		break;
    case 1:
		_setLED(ONE);
		break;
    case 2:
		_setLED(TWO);
		break;
    case 3:
		_setLED(THREE);
		break;
    case 4:
		_setLED(FOUR);
		break;
    case 5:
		_setLED(FIVE);
        break;
    case 6:
		_setLED(SIX);
        break;
    case 7:
		_setLED(SEVEN);
        break;
    case 8:
		_setLED(EIGHT);
        break;
    case 9:
		_setLED(NINE);
		break;
    default:
		_setLED(ERROR);
  }
}
/*
sets the digit defined by the pin parameter, which represents the common annode to the digit defined by number;
@pin - the common annode to light up; 
@number - the digit to display
@decimal - boolean value to light decimal point on true
*/
void CommonAnnodeSSD::_setDigit(int pin, int number, boolean decimal){
    _mapDigit(number);
	if(decimal){
		digitalWrite(_s10,0);  
	}else
	{
		digitalWrite(_s10,1);  
	}
    digitalWrite(pin, HIGH);
    delayMicroseconds(_microsecondsDelay);
    digitalWrite(pin, LOW);
}


/*
converts number from 0-1000 to 4 signigicant digits.
*/
void CommonAnnodeSSD::convertFourDigits(float num){
  boolean dec1000=false;
  boolean dec100=false;
  boolean dec1=false; 
  boolean dec0=false;
  int num2=(int)num;
  
  if(num<10){
	dec1000=true;
	num2=int(num*1000.0);
  }else if(num<100){
	dec100=true;
	num2=int(num*100.0);
  }else if(num<1000){
	 dec1=true;
	 num2=int(num*10.0);
  }else{
	 dec0=true;
  }

  int mod= num2%1000;
  int thousands=(num2-mod)/1000;
  num2 = mod%100;
  int hundreds=(mod-num2)/100;  
  mod=num2%10;
  int tens=(num2-mod)/10; 
  int ones=mod;       
  
  _setDigit(_s1,thousands,dec1000);
  _setDigit(_s4,hundreds,dec100);
  _setDigit(_s5,tens,dec1);
  _setDigit(_s7,ones,dec0);
}




