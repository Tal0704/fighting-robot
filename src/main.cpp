#include <FirebaseESP32.h>
#include <WiFi.h>
#include "macros.h"
#include "../lib/pins.h"
#include <Wheels.h>
#include <laser.h>
#include <servo.h>
#include <misc.h>
#include <Joystick.h>
#include <input.h>

#include <WiFi.h>

static Input lStick;

void setup()
{
	Serial.begin(9600);
	initFirebase();
}

void loop()
{
	lStick.getInputApp();
}