#pragma once
#include <Arduino.h>
#include "pos.h"

// Vcc is 3.3 volts
class Joystick
{
private:
	Position pos;

public:
	Joystick() = delete;

	Joystick(unsigned int x, unsigned int y, unsigned int z);

	int getX() { return (analogRead(this->pos.x) - 1970); } // returns the postion of x where middle is 0
	int getY() { return (analogRead(this->pos.y) - 1920); } // returns the postion of y where middle is 0
	short getZ() { return digitalRead(this->pos.z); }
};