#include "TempAndLight.h"
#include "Arduino.h"

TempAndLight::TempAndLight(uint8_t temp, uint8_t light){
	init(temp, light);
}

void TempAndLight::init(uint8_t temp, uint8_t light)
{
	_temp_pin = temp;
	_light_pin = light;
}

float TempAndLight::getTemp()
{
	temp_clock = analogRead(_temp_pin);
	temp_val = (temp_clock / 1024.0)*500;
	return temp_val;
}

float TempAndLight::getLight()
{
	light_clock = analogRead(_light_pin);
	light_val = light_clock *(5.0/1024.0);
	return light_val;
}
