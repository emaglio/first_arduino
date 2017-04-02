/*
 * MyButton.cpp
 *
 *  Created on: 2Apr.,2017
 *      Author: emaglio
 */

#include "MyLCD.h"
#include "Arduino.h"

//call this to set up the button pin
void MyButton::Begin(uint8_t pin){
	 pinMode(pin, INPUT);
	 digitalWrite(pin, HIGH);
}

int MyButton::CheckButton(){

	return _result;
}
