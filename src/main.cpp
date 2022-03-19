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

void doStream(StreamData data)
{
	if(data.dataPath() == "/angle")
	{
		Serial.printf("Agnle = ");
		printResult(data);
		Serial.print("\n");
	}
	float d = data.floatData();

	if(data.dataPath() == "/strength")
	{
		Serial.printf("Strength = ");
		printResult(data);
		Serial.print("\n");
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
	initFirebase();

	if(!Firebase.beginStream(stream, "processor/controller/leftStick"))
		Serial.printf("Stream begin error, %s\n\n", stream.errorReason().c_str());

	Firebase.setStreamCallback(stream, doStream, doStreamTimeout);
	Serial.println("\nCompleted setup succefully!");
}

void loop()
{

}
