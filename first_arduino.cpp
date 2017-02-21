#include <Arduino.h>
#include <stdlib.h>
#include "LiquidCrystal.h"

#include "TempAndLight.h"

float tempVal;
float lightVal;

TempAndLight sensors(1,0);
LiquidCrystal lcd(13, 7, 8, 9, 10, 11);

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
