#ifndef MyLCD_h
#define MyLCD_h

#include "Print.h"

//flag for function set
#define LCD_4bit 0x00

class MyLCD : public Print{
public:
	void init(uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

	void pulseEnable();

private:
	uint8_t _rs_pin;
	uint8_t _rw_pin;
	uint8_t _enable_pin;
	uint8_t _data_pins[4];

	uint8_t _display_function;
};
#endif
