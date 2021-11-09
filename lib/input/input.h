#pragma once
#include <Arduino.h>
#include "../joystick/Joystick.h"
#include "../pins.h"
#include "../Wheels/Wheels.h"
#include "vector.h"

class Input
{
private:
	Vector input;
	Joystick lStick;

public:
	void moveWheels(Wheels &wheels);
	void getInputController();
	Input();
};