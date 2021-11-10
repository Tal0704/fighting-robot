#pragma once
#include <Arduino.h>
#include "../joystick/Joystick.h"
#include "../pins.h"
#include "../Wheels/Wheels.h"
#include "vector.h"
#include "../controller/controller.h"

class Input
	: public Controller
{
private:
	Vector input;

public:
	void moveWheels(Wheels &wheels);
	void getInputController();
	Input();
};