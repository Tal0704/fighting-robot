#include <inc.h>
#include <WiFi.h>
#include <Wheels.h>
#include <laser.h>
#include <servo.h>
#include <misc.h>
#include <Joystick.h>
#include <input.h>
#include <WiFi.h>
#include <string>
#include <firebaseInit.h>
#include <addons/RTDBHelper.h>

FirebaseData stream;
Wheels wheels;
Vector wheelsDir;

void doStream(StreamData data)
{
	float d = data.floatData();
	if(data.dataPath() == "/angle")
	{
		Serial.printf("Agnle = %.2f\n", d);
		wheelsDir = Vector(d, wheelsDir.strength);
	}

	if(data.dataPath() == "/strength")
	{
		Serial.printf("Strength = %.2f\n", d);
		wheelsDir = Vector(wheelsDir.angle, d);
	}
}

void setup()
{
	Serial.begin(9600);
	initFirebase(WIFI_NAME_HOME, WIFI_PASS_HOME, doStream);
}

void loop()
{
	
}
