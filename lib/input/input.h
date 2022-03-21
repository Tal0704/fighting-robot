#pragma once
#include <vector.h>
#include <Wheels.h>
#include <esp_now.h>
#include <Arduino.h>
#include <Joystick.h>
#include <controller.h>
#include <FirebaseESP32.h>

#define WROVER_E_MAC                            \
	{                                           \
		0x78, 0xE3, 0x6D, 0xCD, 0x07, 0x68 \
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