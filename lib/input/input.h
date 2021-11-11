#pragma once
#include <Arduino.h>
#include <FirebaseESP32.h>
#include <vector.h>
#include <Wheels.h>
#include <Joystick.h>
#include <controller.h>
#include <pthread.h>
#include "../pins.h"

class Input
	: public Controller
{
private:
	Vector input;
	// void *reciveFunc(void *reciveFunc);

public:
	void moveWheels(Wheels &wheels);
	void getInputController();
	void getInputApp();
};