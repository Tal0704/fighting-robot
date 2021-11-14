#pragma once
#include <vector.h>
#include <Wheels.h>
#include <esp_now.h>
#include <Arduino.h>
#include <Joystick.h>
#include <controller.h>
#include <FirebaseESP32.h>
#include "../pins.h"

#define WROVER_E_MAC                            \
	{                                           \
		0x78, 0xE3, 0x6D, 0xCD, 0x07, 0x68 \
	}
#define WROVER_MAC                              \
	{                                           \
		0x94, 0xB9, 0x7E, 0xE2, 0x98, 0x50 \
	}

class Input
	: public Controller
{
private:
	Vector input;
	friend void *reciveFunc(void *);

public:
	void moveWheels(Wheels &wheels);
	void getInputController();
	void getInputApp();
};