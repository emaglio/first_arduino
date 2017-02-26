#include "MyLCD.h"
#include "Arduino.h"

MyLCD::MyLCD(uint8_t rs, uint8_t enable,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7){
	init(rs, enable, d4, d5, d6, d7);
}

void MyLCD::init(uint8_t rs, uint8_t enable,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
	_rs_pin = rs;
	_enable_pin = enable;

	_data_pins[0] = d4;
	_data_pins[1] = d5;
	_data_pins[2] = d6;
	_data_pins[3] = d7;

//	begin(16,1);
}

void MyLCD::begin(uint8_t cols, uint8_t lines){
//	setup digital as OUTPUT
	pinMode(_rs_pin, OUTPUT);

	for(int i = 0; i < 4; i++){
		pinMode(_data_pins[i], OUTPUT);
	}

//	set low rs and enable to send the instructions
	delayMicroseconds(50000);
	digitalWrite(_rs_pin, LOW);
	digitalWrite(_enable_pin, LOW);

//	send twice the 4bits setup
	write4bits(0x02);
	delayMicroseconds(4500);

	write4bits(0x02);
}

void MyLCD::write4bits(uint8_t value){
	for(int i = 0; i < 4; i++){
		digitalWrite(_data_pins[i], (value >> i) & 0x01);
	}
}

void MyLCD::pulseEnable(void) {
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(1);
  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
}

inline size_t MyLCD::write(uint8_t value) {
  send(value, HIGH);
  return 1; // assume sucess
}

// write either command or data
void MyLCD::send(uint8_t value, uint8_t mode) {
  digitalWrite(_rs_pin, mode);

  write4bits(value>>4);
  write4bits(value);
}



