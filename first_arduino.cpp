#include <Arduino.h>
#include <stdlib.h>

#include "/first_arduino/libraries/LiquidCrystal/LiquidCrystal.h"
#include "/first_arduino/libraries/TempAndLight/TempAndLight.h"
#include "/first_arduino/libraries/MyLCD/MyLCD.h"
#include "/first_arduino/libraries/MyButton/MyButton.h"

float tempVal;
float lightVal;

//buzzer pin
const uint8_t buzzer_pin = 13;

//Menu
char* level_1[3] = {"1","Sensors", "RBG LED"};
char* level_1_1[4] {"1-1","Temperature", "Light", "<- BACK"};
char* level_1_1_1[4] {"1-1-1","ON", "OFF", "<- BACK"};
char* level_1_2[6] {"1-2","Blue", "Green", "Red", "OFF", "<- BACK"};
long current_ok_counter = 0;
long current_scroll_counter = 0;
long ok_counter = 0;
long scroll_counter = 0;
int ok_result = 0;
int scroll_result = 0;
int size_array;

//button pins configuration
#define ok_pin 18
#define scroll_pin 19

//dim of menu_array
// num_array --> number of arrays
// dim_array --> biggest array
#define num_array 4
#define dim_array 6

//menu_array to identify the correct array to show
char* menu_array[num_array][dim_array];
//index to match with the first element of the arrays
//up to 5 levels
char index[] = {"1-/-/-/-/"};
//dim of the index, change this if adding/removing levels in index
int index_dim = 9;
//used to get the correct array
int remainder = 0;
int menu_array_row = 0;

//libraries
TempAndLight sensors(0,1);
MyLCD lcd(11,12,7,6,5,4);
MyButton ok(ok_pin);
MyButton scroll(scroll_pin);

//Event functions
void buzzer(){
	tone(buzzer_pin, 1000);
	delay(500);
	noTone(buzzer_pin);
}

void ok_event(){
	ok_counter += 1;
}

void ok_double(){
	ok_counter += 2;
	remainder = 0;
}

void scroll_event(){
	scroll_counter += 1;
}

int getSizeArray(){
	int i = 1;
	while(i < dim_array){
		const char* temp = menu_array[menu_array_row][i];
		if(temp == "nil"){
			break;
		}else{
			i++;
		}
	}

	if(i < dim_array){
		i++;
	}
	return i;
}

void write_to_lcd(int offset){
	lcd.clean();

	int index_first_line, index_second_line;

	size_array = getSizeArray();

	remainder = offset % size_array;

	// get the array from menu_array
	// without the first element which is the index
	const char* array[size_array-1];
	for(int i = 0; i < (size_array-1); i++){
		array[i] = menu_array[menu_array_row][i+1];
	}

	//set the pointer "<-"
	if(offset == 0){
		lcd.setCursor(14, 0);
		lcd.print("<-");
	}else{
		lcd.setCursor(14, 0);
		lcd.print("  ");
		lcd.setCursor(14, 1);
		lcd.print("<-");
	}

	//set index first and second line
	if(offset <= 1){
		index_first_line = 0;
		index_second_line = 1;
	}else{
		index_first_line = remainder-1;
		index_second_line = index_first_line + 1;
	}

	//showing last value first line
	//and first value second line
	if(remainder == 0 && offset > 1){
		index_first_line = size_array;
		index_second_line = 0;
	}

	//first line
	lcd.setCursor(0,0);
	lcd.print(index_first_line);
	lcd.setCursor(1,0);
	lcd.print(")");
	lcd.setCursor(3,0);
	lcd.print(array[index_first_line]);

	if(size_array > 2){
		//second line
		lcd.setCursor(0,1);
		lcd.print(index_second_line);
		lcd.setCursor(1,1);
		lcd.print(")");
		lcd.setCursor(3,1);
		lcd.print(array[index_second_line]);
	}
}

int getLength(char text[]){
	int dim = index_dim;
	int i=0;
	while(i<dim){
		if(text[i] == '/'){
			break;
		}else{
			i++;
		}
	}
	if(i == dim){
		i = dim;
	}else{
		i= i-1;
	}
	return i;
}

//find correct array in base on index value in menu_array
void getMenuRow(){
	int length = getLength(index);
	int value;
	char temp[20];
	for(int i=0; i<num_array; i++){
		for(int j=0; j<length; j++){
			strcpy(temp, menu_array[i][0]);
			if(temp[j] != index[j]){
				break;
			}
		}
		value = i;
	}
	menu_array_row = value;
}

//replace / with num to create the correct index
void nextLevel(int num){
	int i = 0;
	// find the first / available
	while(i<index_dim){
		if(index[i] == '/'){
			break;
		}else{
			i++;
		}
	}

	// int to char and set the new char_num in the correct position
	char char_num = '0' + num;
	if(i < index_dim){
		index[i] = char_num;
	}
}

// replace last number with / to go back in the menu
void backLevel(){
	int i = 0;
	while(i<index_dim){
		if(index[i] == '/'){
			break;
		}else{
			i++;
		}
	}

	if(i == index_dim){
		index[i-1] = '/';
	}else{
		if(i < index_dim and i > 2){
			index[i-2] = '/';
		}
	}

}

void ok_control(){
	ok_result = ok.checkButton();

	if(ok_result == 1){
		ok_event();
		// update index using reminder + 1 because the index starts from 1 not 0 as the array
		nextLevel(remainder+1);
		// reset write-lcd-index = remainder
		remainder = 0;
		// find new menu array row
		getMenuRow();
	}

	if(ok_result == 2){
		ok_double();
		backLevel();
		remainder = 0;
		getMenuRow();
	}
}

void scroll_control(){
	scroll_result = scroll.checkButton();

	if(scroll_result == 1){
		scroll_event();
	}
}

void addArray(int row, char* array[], int dim){
	for(int i=0; i<dim; i++){
		menu_array[row][i] = array[i];
	}

	for(int i=dim-1; i<dim_array; i++){
		menu_array[row][i] = "nil";
	}
}



void setup() {
	Serial.begin(115200);

	pinMode(ok_pin, INPUT);
	digitalWrite(ok_pin, HIGH);

	//columns, rows, font (58 -> 5x8 or 511 -> 5x11)
	lcd.begin(16,2,58);

	//set up buttons
	ok.begin(ok_pin);
	scroll.begin(scroll_pin);

	//create menu array
	addArray(0, level_1, 3);
	addArray(1, level_1_1, 4);
	addArray(2, level_1_1_1, 4);
	addArray(3, level_1_2, 6);

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
	ok_control();
	// wait for the first OK click
	if(ok_counter == 0){
		lcd.setCursor(0,0);
		lcd.print("Click OK to");
		lcd.setCursor(0,1);
		lcd.print("continue...");
	}else{
		write_to_lcd(0);
		while(true){
			// TODO: need to understand what happen to index
			Serial.print(index);
			//Here all the code for the menu
			ok_control();
			scroll_control();
			//one of the button has been pressed
			if(current_scroll_counter != scroll_counter or current_ok_counter != ok_counter){
				write_to_lcd(current_scroll_counter);
				current_scroll_counter = scroll_counter;
				current_ok_counter = ok_counter;
			}
		}
	}

}
