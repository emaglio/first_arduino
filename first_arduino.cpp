#include <Arduino.h>

int pinLight = 1; //photoresistor
int lightClock = 0; //light in clock
float lightVal = 0; //result from photoresistor
int pintTemp = 0; //temp sensor
float tempVal = 0; //result from temp sensor


void setup() {
	Serial.begin(115200);
}

void loop() {
	lightClock = analogRead(pinLight);
	Serial.print("Light: ");
	Serial.print(lightClock);
	Serial.println(" clock");
	Serial.print("Light: ");
	lightVal = lightClock*(5.0/1024.0);
	Serial.print(lightVal);
	Serial.println(" V");
	tempVal = analogRead(pintTemp);
	tempVal = (tempVal / 1024.0)*500;
	Serial.print("Temp:");
	Serial.print(tempVal);
	Serial.println(" C");
	delay(500);
}
