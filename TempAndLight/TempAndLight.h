#ifndef TempAndLight_h
#define TempAndLight_h

#include "Arduino.h"

class TempAndLight {
public:
	TempAndLight(uint8_t temp, uint8_t light);
	void init(uint8_t temp, uint8_t light);
	float getTemp();
	float getLight();

private:
	uint8_t _temp_pin;
	uint8_t _light_pin;
	uint16_t light_clock;
	uint16_t temp_clock;
	float temp_val = 0 ;
	float light_val = 0;
};
#endif
