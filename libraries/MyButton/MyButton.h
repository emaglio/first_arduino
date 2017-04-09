/*
 * MyButton.h
 *
 *  Created on: 2Apr.,2017
 *      Author: emaglio
 */

//Button has been pressed when HIGH is detected

#include <inttypes.h>

#ifndef MyButton_h
#define MyButton_h

class MyButton {
public:
	MyButton(uint8_t pin);
	void init(uint8_t pin);
	void begin(uint8_t pin);
	int checkButton();
	void readButton();
	void getButtonEvents();
	void checkResult();


private:
	//button time variables
	int _button_pin = 0;
	int _debounce = 20;			// ms debounce period to prevent flickering when pressing or releasing the button
	int _DCgap = 250;			// ms hold period: how long to wait for press+hold event
	int _holdTime = 1000;		// ms long hold period: how long to wait for press+hold event
	int _longHoldTime = 3000;	// ms long hold period: how long to wait for press+hold event

	//button variables
	int result = 0;					//1 click ones, 2 double click, 3 hold and 4 long hold
	bool _buttonVal = false;  		//true = HIGH, false = LOW
	bool _previousVal = false; 		//true = HIGH, false = LOW
	long _timeUp = 0; 				//time when button has been release
	long _timeDown = 0; 			//time when button has been pressed
	int _timePressed = 0; 			//time button pressed down
	long _timeBetweenDowns = 300;	//time between 2 consecutive button switch
	int _event = 0; 				//number of times the button is pressed successfully
	bool _buttonClicked = false;	//flag to confirm the button has been pressed correctly

};

#endif /* MyButton_h */
