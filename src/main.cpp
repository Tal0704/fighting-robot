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
#include <string>
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

void doStreamTimeout(bool timeout)
{
	if(timeout)
		Serial.println("Stream timed out, resuming...\n");

	if(!stream.httpConnected())
		Serial.printf("Error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}

void setup()
{
	Serial.begin(9600);
	initFirebase("Meron-1", "0545668998");

	if(!Firebase.beginStream(stream, "processor/controller/leftStick"))
		Serial.printf("Stream begin error, %s\n\n", stream.errorReason().c_str());

	Firebase.setStreamCallback(stream, doStream, doStreamTimeout);
	Serial.println("\nCompleted setup succefully!");
}

void loop()
{
	
}
