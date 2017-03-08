#include <Arduino.h>
#include <stdlib.h>
#include "/first_arduino/libraries/LiquidCrystal/LiquidCrystal.h"

#include "/first_arduino/libraries/TempAndLight/TempAndLight.h"
#include "/first_arduino/libraries/MyLCD/MyLCD.h"

float tempVal;
float lightVal;

TempAndLight sensors(0,1);
//LiquidCrystal lcd(11,12,5,4,3,2);

MyLCD lcd(11,12,5,4,3,2);


void setup() {
	Serial.begin(115200);
	//columns, rows, font (58 -> 5x8 or 511 -> 5x11)
	lcd.begin(16,2,58);
}

void loop() {
	lcd.setCursor(0,0);
	lcd.print("Trailblazer");
	lcd.setCursor(6,1);
	lcd.print("PowerUser");

//	lcd.print("Hello world!");
//	Serial.println("Check Hello World");
//	delay(4000);
//	Serial.println("Cleaning display");
//	lcd.clean();
//	tempVal = sensors.getTemp();
//	lightVal = sensors.getLight();
//	Serial.print("Light: ");
//	Serial.print(lightVal);
//	Serial.println(" V");
//	Serial.print("Temp:");
//	Serial.print(tempVal);
//	Serial.println(" C");

//	lcd.setCursor(0, 0);
//	Serial.println("Write temp");
//	lcd.print(tempVal);
//	delay(1000);
}
