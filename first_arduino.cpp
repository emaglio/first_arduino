#include <Arduino.h>
#include <stdlib.h>

#include "/first_arduino/libraries/LiquidCrystal/LiquidCrystal.h"
#include "/first_arduino/libraries/TempAndLight/TempAndLight.h"
#include "/first_arduino/libraries/MyLCD/MyLCD.h"
#include "/first_arduino/libraries/MyButton/MyButton.h"

float tempVal;
float lightVal;

//these must be volatile to be used in the interrupt
long ok_counter = 0;
long scroll_counter = 0;
//first OK pressed to start the menu
int start_menu = 0;

//buzzer pin
const uint8_t buzzer_pin = 13;

//Menu
char* level_1[6] = {"1","Sensors", "RBG LED", "Erin", "Mani", "Doggy dog"};
char* level_1_1[4] {"1-1","Temperature", "Light", "<- BACK"};
char* level_1_1_1[4] {"1-1-1","ON", "OFF", "<- BACK"};
char* level_1_2[6] {"1-2","OFF", "Blue", "Green", "Red", "<- BACK"};
char* level_1_3[2] {"1-3","<- BACK"};
int level_1_counter = 0;
int level_1_1_counter = 0;
int level_1_2_counter = 0;
bool level_2 = false;
int current_ok_counter = 0;
int current_scroll_counter = 0;
int ok_result = 0;
int scroll_result = 0;

int size_array;

//button pins configuration
#define ok_pin 18
#define scroll_pin 19

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
}

void scroll_event(){
	scroll_counter += 1;
}

void write_to_lcd(char* array[], int size_array, int offset){
	lcd.clean();

	int remainder, index_first_line, index_second_line;

	remainder = offset % size_array;

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
		index_first_line = remainder - 1;
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

	//second line
	lcd.setCursor(0,1);
	lcd.print(index_second_line);
	lcd.setCursor(1,1);
	lcd.print(")");
	lcd.setCursor(3,1);
	lcd.print(array[index_second_line]);
}

void ok_control(){
	ok_result = ok.checkButton();

	if(ok_result == 1){
		ok_event();
	}

	if(ok_result == 2){
		ok_double();
	}
}

void scroll_control(){
	scroll_result = scroll.checkButton();

	if(scroll_result == 1){
		scroll_event();
	}
}

//dim of menu_array
// num_array --> number of arrays
// dim_array --> biggest array
#define num_array 5
#define dim_array 6

//menu_array to identify the correct array to show
char* menu_array[num_array][dim_array];
//index to match with the first element of the arrays
//up to 5 levels
char index[] = {"1-/-/-/-/"};
//dim of the index, change this if adding/removing levels in index
int index_dim = 9;

void addArray(int row, const char* array[], int dim){
	for(int i=0; i<dim; i++){
		menu_array[row][i] = array[i];
	}

	for(int i=dim-1; i<dim_array; i++){
		menu_array[row][i] = "nil";
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

int getMenuRow(char index[]){
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
	return value;
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
	addArray(0, level_1, 6);
	addArray(1, level_1_1, 4);
	addArray(2, level_1_1_1, 4);
	addArray(3, level_1_2, 6);
	addArray(5, level_1_3, 2);

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

	Serial.print(ok_counter);
}

void loop() {
	ok_result = ok.checkButton();

	if(ok_result == 1){
		ok_event();
	}

	if(start_menu == 0 and ok_counter == 0){
		lcd.setCursor(0,0);
		lcd.print("Click OK to");
		lcd.setCursor(0,1);
		lcd.print("continue...");
	}else{
		size_array = (sizeof(level_1)/sizeof(char))/2;
		write_to_lcd(level_1, size_array, 0);
		while(true){
			//Here all the code for the menu
			ok_control();
			scroll_control();
			//scroll event
			if(current_scroll_counter != scroll_counter){
				size_array = (sizeof(level_1)/sizeof(char))/2;
				write_to_lcd(level_1, size_array, current_scroll_counter+1);
				current_scroll_counter = scroll_counter;
			}

			if(current_ok_counter != ok_counter){

			}
		}
	}

}
