#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

#include "/first_arduino/libraries/LiquidCrystal/LiquidCrystal.h"
#include "/first_arduino/libraries/TempAndLight/TempAndLight.h"
#include "/first_arduino/libraries/MyLCD/MyLCD.h"
#include "/first_arduino/libraries/MyButton/MyButton.h"

float tempVal;
float lightVal;

//these must be volatile to be used in the interrupt
volatile int ok_counter = 0;
volatile int scroll_counter = 0;
//first OK pressed to start the menu
int start_menu = 0;


//button pins
const uint8_t ok_pin = 3;
const uint8_t scroll_pin = 2;

//buzzer pin
const uint8_t buzzer_pin = 13;

//Menu
const char* level_1[3] {"Sensors", "RBG LED", "TBD"};
const char* level_1_1[3] {"Temperature", "Light", "<- BACK"};
const char* level_1_2[5] {"OFF", "Blue", "Green", "Red", "<- BACK"};
const char* level_1_3[1] {"<- BACK"};
int level_1_counter = 0;
int level_1_1_counter = 0;
int level_1_2_counter = 0;
bool level_2 = false;
int current_ok_counter = 0;
int current_scroll_counter = 0;
int ok_result = 0;
int scroll_result = 0;

int size_array;

//pin configuration
#define ok_pin 18
#define scroll_pin 19

//libraries
TempAndLight sensors(0,1);
MyLCD lcd(11,12,7,6,5,4);
MyButton ok(4);
MyButton scroll(5);

//Event functions
void buzzer(){
	tone(buzzer_pin, 1000);
	delay(500);
	noTone(buzzer_pin);
}

void ok_event(){
	Serial.println("ok");
	ok_counter += 1;
}

void scroll_event(){
	Serial.println("scroll");
	scroll_counter += 1;
}

void write_to_lcd(const char* array[], int size_array, int offset){
	lcd.clean();

	int remainder, index_first_line, index_second_line;

	remainder = offset % size_array;
	index_first_line = remainder;
	index_second_line = remainder + 1;

	if(remainder == (size_array - 1)){
		index_first_line = 0;
	}

	//set the pointer "<-"
	if(offset==0){
		lcd.setCursor(14, 0);
		lcd.print("<-");
	}else{
		lcd.setCursor(14, 0);
		lcd.print("  ");
		lcd.setCursor(14, 1);
		lcd.print("<-");
	}

	Serial.println(size_array);
	Serial.println(remainder);
	Serial.println(offset);
	Serial.println(index_first_line);
	Serial.println(index_second_line);

	//first line
	lcd.setCursor(0,0);
	lcd.print(index_first_line);
	lcd.setCursor(1,0);
	lcd.print(")");
	lcd.setCursor(3,0);
	lcd.print(array[index_first_line]);

	//second line
	lcd.setCursor(0,1);
	lcd.print(index_second_line);
	lcd.setCursor(1,1);
	lcd.print(")");
	lcd.setCursor(3,1);
	lcd.print(array[index_second_line]);
}

void setup() {
	Serial.begin(115200);

	//columns, rows, font (58 -> 5x8 or 511 -> 5x11)
	lcd.begin(16,2,58);

	ok.begin(ok_pin);
	scroll.begin(scroll_pin);

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
//	if(start_menu == 0 and ok_counter == 0){
//		lcd.setCursor(0,0);
//		lcd.print("Click OK to");
//		lcd.setCursor(0,1);
//		lcd.print("continue...");
//	}else{
//		size_array = (sizeof(level_1)/sizeof(char))/2;
//		write_to_lcd(level_1, size_array, 0);
//		while(true){
//			//Here all the code for the menu
//
//			//scroll event
//			if(current_scroll_counter != scroll_counter){
//				size_array = (sizeof(level_1)/sizeof(char))/2;
//				write_to_lcd(level_1, size_array, current_scroll_counter+1);
//				current_scroll_counter = scroll_counter;
//			}
//
//			if(current_ok_counter != ok_counter){
//
//			}
//		}
//	}

	ok_result = ok.checkButton();

	Serial.println(digitalRead(ok_pin));

	if(ok_result == 1){
		lcd.clean();
		lcd.setCursor(0,0);
		lcd.print("Just a click");
	}

	if(ok_result == 2){
		lcd.clean();
		lcd.setCursor(0,0);
		lcd.print("Double Click");
	}

	if(ok_result == 3){
		lcd.clean();
		lcd.setCursor(0,0);
		lcd.print("Hold Click");
	}

	if(ok_result == 4){
		lcd.clean();
		lcd.setCursor(0,0);
		lcd.print("Long Hold Click");
	}
}
