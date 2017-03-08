#ifndef MyLCD_h
#define MyLCD_h

#include <inttypes.h>
#include "Print.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

//flag for function set
#define LCD_CLEAN 0x00
#define LCD_4BITS 0x00
#define LCD_1LINE 0x00
#define LCD_2LINE 0x08
#define LCD_5x8DOTS 0x00
#define LCD_5x11DOTS 0x04

//flag for display ON/OFF
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00


class MyLCD : public Print{
public:
	MyLCD(uint8_t rs, uint8_t enable,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	void init(uint8_t rs, uint8_t enable,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

	void begin(uint8_t cols, uint8_t lines, uint8_t font);

	void clean();
	void home();

	void display();
	void noDisplay();
	void cursor();
	void noCursor();
	void blink();
	void noBlink();
	void setCursor(uint8_t column, uint8_t row);

	void setRowOffsets(int row1, int row2, int row3, int row4);
	void command(uint8_t value);
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

	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;
	uint8_t _num_lines;
	uint8_t _row_offsets[4];
};
#endif
