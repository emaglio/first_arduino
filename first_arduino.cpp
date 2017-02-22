#include <Arduino.h>
#include <stdlib.h>
#include "/first_arduino/libraries/LiquidCrystal/LiquidCrystal.h"

#include "/first_arduino/libraries/TempAndLight/TempAndLight.h"

float tempVal;
float lightVal;

TempAndLight sensors(0,1);
LiquidCrystal lcd(7,0,1,2,3,4,5);

void setup() {
	Serial.begin(115200);

	lcd.begin(16, 2);

	lcd.print("Hello world!");
}

void loop() {
	tempVal = sensors.getTemp();
	lightVal = sensors.getLight();
	Serial.print("Light: ");
	Serial.println(" clock");
	Serial.print("Light: ");
	Serial.print(lightVal);
	Serial.println(" V");
	Serial.print("Temp:");
	Serial.print(tempVal);
	Serial.println(" C");

	lcd.setCursor(0, 1);
	lcd.print(tempVal);

	delay(500);
}
