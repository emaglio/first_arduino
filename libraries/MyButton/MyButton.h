/*
 * MyButton.h
 *
 *  Created on: 2Apr.,2017
 *      Author: emaglio
 */

#ifndef MyButton_h
#define MyButton_h

class MyButton {
public:
	void Begin(uint8_t pin);
	int CheckButton();

private:
	//button time variables
	int _debounce = 20;			// ms debounce period to prevent flickering when pressing or releasing the button
	int _DCgap = 250;			// ms hold period: how long to wait for press+hold event
	int _holdTime = 1000;		// ms long hold period: how long to wait for press+hold event
	int _longHoldTime = 3000;	// ms long hold period: how long to wait for press+hold event

	//button variables
	int _result = 0;	//1 click ones, 2 double click, 3 hold time, 4 long hold time
	boolean currentVal = true;  //true = HIGH, false = LOW
	boolean previousVal = true; //true = HIGH, false = LOW

};

#endif /* MyButton_h */
