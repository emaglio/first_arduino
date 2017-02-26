#ifndef MyLCD_h
#define MyLCD_h

#include <inttypes.h>
#include "Print.h"

//flag for function set
#define LCD_4bit 0x00

class MyLCD : public Print{
public:
	MyLCD(uint8_t rs, uint8_t enable,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	void init(uint8_t rs, uint8_t enable,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

	void begin(uint8_t cols, uint8_t lines);
	virtual size_t write(uint8_t);
	using Print::write;
private:
	void send(uint8_t, uint8_t);
	void write4bits(uint8_t value);
	void pulseEnable();

	uint8_t _rs_pin;
	uint8_t _rw_pin;
	uint8_t _enable_pin;
	uint8_t _data_pins[4];

	uint8_t _display_function;
};
#endif
