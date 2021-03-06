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

	begin(16,2,58);
}

void MyLCD::begin(uint8_t cols, uint8_t lines, uint8_t font){
	//setup digital as OUTPUT
	pinMode(_rs_pin, OUTPUT);
	pinMode(_enable_pin, OUTPUT);

	_num_lines = lines;
	setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

	for(int i = 0; i < 4; i++){
		pinMode(_data_pins[i], OUTPUT);
	}

	//default 4 bits, 1 line and 5x8 dots as font
	_displayfunction = LCD_4BITS | LCD_1LINE | LCD_5x8DOTS;

	if(lines == 2){
		_displayfunction |= LCD_2LINE;
	}

	if(font == 511){
		_displayfunction |= LCD_5x11DOTS;
	}

	//set low rs and enable to send the instructions
	delayMicroseconds(50000);
	digitalWrite(_rs_pin, LOW);
	digitalWrite(_enable_pin, LOW);

	//trying to force the 8bits (apparently necessary)
	//3 times
	write4bits(0x03);
	delayMicroseconds(4500);

	write4bits(0x03);
	delayMicroseconds(4500);

	write4bits(0x03);
	delayMicroseconds(150);

	//finally set 4bits
	write4bits(0x02);

	//Set bits, lines and font
	command(LCD_FUNCTIONSET | _displayfunction);

	noDisplay();
	//turn the display ON, no blinking, no cursor
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();

	//clean display
	clean();

	// Initialize to default text direction (for romance languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);
}

void MyLCD::write4bits(uint8_t value){
	for(int i = 0; i < 4; i++){
		digitalWrite(_data_pins[i], (value >> i) & 0x01);
	}

	pulseEnable();
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
// needs to send the 4btis twice
void MyLCD::send(uint8_t value, uint8_t mode) {
  digitalWrite(_rs_pin, mode);

  write4bits(value>>4);
  write4bits(value);
}

void MyLCD::command(uint8_t value){
	send(value, LOW);
}

//Clear all display data
void MyLCD::clean(){
	command(LCD_CLEARDISPLAY);
	delayMicroseconds(2000);
}

//turn the display ON
void MyLCD::display(){
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

//turn the display OFF
void MyLCD::noDisplay(){
	_displaycontrol &= ~LCD_DISPLAYOFF;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

//turn the cursor ON
void MyLCD::cursor(){
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

//turn the cursor OFF
void MyLCD::noCursor(){
	_displaycontrol &= ~LCD_CURSOROFF;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

//turn the blink ON
void MyLCD::blink(){
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

//turn the blink OFF
void MyLCD::noBlink(){
	_displaycontrol &= ~LCD_BLINKOFF;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

//set the AC address in base on the
void MyLCD::setRowOffsets(int row0, int row1, int row2, int row3)
{
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}


//Set the position of the cursor
void MyLCD::setCursor(uint8_t col, uint8_t row){
	const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
	if ( row >= max_lines ) {
		row = max_lines - 1;    // we count rows starting w/0
	}
	if ( row >= _num_lines ) {
		row = _num_lines - 1;    // we count rows starting w/0
	}

	command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

//Shift display to the right
void MyLCD::shiftDisplayRight(){
	command(LCD_CURSORDISPLAYSHIFT | LCD_DISPLAY | LCD_MOVERIGHT);
}

//Shift display to the left
void MyLCD::shiftDisplayLeft(){
	command(LCD_CURSORDISPLAYSHIFT | LCD_DISPLAY | LCD_MOVELEFT);
}


