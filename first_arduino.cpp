#include <Arduino.h>
#include <stdlib.h>
#include "/first_arduino/libraries/LiquidCrystal/LiquidCrystal.h"

#include "/first_arduino/libraries/TempAndLight/TempAndLight.h"
#include "/first_arduino/libraries/MyLCD/MyLCD.h"

float tempVal;
float lightVal;

//these must be volatile to be used in the interrupt
volatile int ok_counter = 0;
volatile int scroll_counter = 0;
//first OK pressed to start the menu
volatile int start_menu = 0;


//button pins
const uint8_t ok_pin = 3;
const uint8_t scroll_pin = 2;

//buzzer pin
const uint8_t buzzer_pin = 13;

//Menu
const char* level_1[2] {"Sensors", "RBG LED"};
const char* level_1_1[3] {"Temperature", "Light", "<- BACK"};
const char* level_1_2[5] {"OFF", "Blue", "Green", "Red", "<- BACK"};
int level_1_counter = 0;
int level_1_1_counter = 0;
int level_1_2_counter = 0;

//libraries
TempAndLight sensors(0,1);
MyLCD lcd(11,12,7,6,5,4);

//Event functions
void buzzer(){
	tone(buzzer_pin, 1000);
	delay(500);
	noTone(buzzer_pin);
}

void ok(){
	Serial.println("ok");
	ok_counter += 1;
}

void scroll (){
	Serial.println("scroll");
	scroll_counter += 1;
}

void setup() {
	Serial.begin(115200);

	//columns, rows, font (58 -> 5x8 or 511 -> 5x11)
	lcd.begin(16,2,58);

	//using internal pullup resistor
	pinMode(ok_pin, INPUT_PULLUP);
	pinMode(scroll_pin, INPUT_PULLUP);
	//set up the interrupt pin, what to call and when to call it
	attachInterrupt(digitalPinToInterrupt(ok_pin), ok, RISING);
	attachInterrupt(digitalPinToInterrupt(scroll_pin), scroll, RISING);

	//buzzer set up
	pinMode(buzzer_pin, OUTPUT);

	//Start-up with something in the display
	lcd.setCursor(2,0);
	lcd.print("Welcome to:");
	lcd.setCursor(1,1);
	lcd.print("First Arduino");
	delay(4000);
	lcd.clean();
	delay(1000);
}

void loop() {
	if(start_menu == 0 and ok_counter == 0){
		lcd.setCursor(0,0);
		lcd.print("Click OK to");
		lcd.setCursor(0,1);
		lcd.print("continue...");
	}else{
		while(true){
			//Here all the code for the menu
			lcd.clean();
			lcd.setCursor(0,0);
			lcd.print("Menu");
			delay(250);
		}
	}


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
