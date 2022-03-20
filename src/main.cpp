#include "preprocess.h"
#include <WiFi.h>
#include "../lib/pins.h"
#include <Wheels.h>
#include <laser.h>
#include <servo.h>
#include <misc.h>
#include <Joystick.h>
#include <input.h>
#include <WiFi.h>

#define LED 19
#define FREQ 5e3
#define CHANNEL 0

void setup()
{
	ledcSetup(CHANNEL, FREQ, 8);

	ledcAttachPin(LED, CHANNEL);
}

void loop()
{
	for (size_t i = 0; i < 0xFF; i++)
	{
		ledcWrite(0, i);
		delay(15);
	}

	for (size_t i = 0xFF; i > 0; i--)
	{
		ledcWrite(0, i);
		delay(15);
	}
}
