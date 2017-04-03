/*
 * MyButton.cpp
 *
 *  Created on: 2Apr.,2017
 *      Author: emaglio
 */

#include "MyButton.h"
#include "Arduino.h"

MyButton::MyButton(uint8_t pin){
	init(pin);
}

void MyButton::init(uint8_t pin){
	_button_pin = pin;
	_event = 0;

	begin(pin);
}
//call this to set up the button pin
void MyButton::begin(uint8_t pin){
	 pinMode(pin, INPUT);
	 digitalWrite(pin, HIGH);
}

int MyButton::checkButton(){
	readButton();
	getButtonEvents();
	checkResult();

	return result;
}

void MyButton::readButton(){
	// read button
	if(digitalRead(_button_pin) == 1){
		_buttonVal = true;
	}else{
		_buttonVal = false;
	}
}

void MyButton::getButtonEvents(){
	// button pressed
	if(_buttonVal == true && _previousVal == false && (millis()-_timeUp) > _debounce){
		//set timing variables
		if(_event >= 1 && _buttonClicked == true){
			_timeBetweenDowns = millis() - _timeUp;
		}
		_timeDown = millis();

		//
		_previousVal = true;

		//reset variables
		result = 0;
		_buttonClicked = false;

	// button released
	}else if(_buttonVal == false && _previousVal == true && (millis()-_timeDown) > _debounce){
		_timeUp = millis();
		_timePressed = _timeUp - _timeDown;
		_event += 1;
		_buttonClicked = true;
	}
}

void MyButton::checkResult(){
	//check results only if the button has been successfully clicked
	if(_buttonClicked == true){
		// double click
		if(_event >= 1 && _timeBetweenDowns < 250){
			result = 2;
		}
		// hold
		if(_timePressed > 1000 && _timePressed < 3000){
			result = 3;
		}
		// long hold
		if(_timePressed > 3000){
			result = 3;
		}
		// normal click
		if(result == 0){
			result = 1;
		}
	}
}
