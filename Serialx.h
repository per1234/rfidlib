#ifndef SERIAL_X
#define SERIAL_X


#include "Arduino.h"
#include "std.h"

#define S_SOFTWARE 1
#define S_HARDWARE 2


class Serialx
	: SoftwareSerial {
private:
	void * hwSerial;
	unsigned char serialType;

public:
#pragma region Construction
	Serialx(const SoftwareSerial& ser) 
		: SoftwareSerial(ser) {
		this->serialType = S_SOFTWARE;
	}
	Serialx(const HardwareSerial& hser) 
		: SoftwareSerial(254,255) {
		this->serialType = S_HARDWARE;
		this->hwSerial = (void*)&hser;
	}
	///software serial bug here..
	Serialx(unsigned char rx, unsigned char tx, unsigned char stype, bool inverse = false )  
		: SoftwareSerial(rx,tx, inverse) {
		this->serialType = stype;
	}
#pragma endregion

#pragma region Public methods
	using SoftwareSerial::begin;
#pragma endregion

#pragma region Operators

	friend Serialx& operator << (Serialx& ser, based val){
		switch (ser.serialType){
		case 1: ser.print(val.value);  break;
		case 2: ((HardwareSerial*)ser.hwSerial)->print(val.value); break;
		}
	}
	friend  Serialx& operator << (Serialx& ser, int val){
		switch (ser.serialType){
		case 1: ser.print(val);  break;
		case 2: ((HardwareSerial*)ser.hwSerial)->print(val); break;
		}
	}

#pragma endregion


};


#endif