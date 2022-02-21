#include <math.h>
#include <Arduino.h>
#include <WiFi.h>
#include <Firebase.h>
#include "misc.h"
#include "../pins.h"
#include "../../src/preprocess.h"

unsigned int getDistance()
{
	long duration;

	// start of waking call for the sensor
	digitalWrite(TRIG, LOW);
	delayMicroseconds(2);

	// end of waking call for the sensor
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);

	// sending a signal and seeing the
	// duration that it takes to get back
	digitalWrite(TRIG, LOW);
	duration = pulseIn(ECHO, HIGH);

	// returning the distance in cm
	return duration / 29 / 2;
}

// Activating the buzzer
void buzz(unsigned int delay_ms)
{
	// Output '0' to BUZZER_PIN pin (make sound)
	digitalWrite(BUZZER_PIN, LOW);
	delay(delay_ms);
	// Output '1' to BUZZER_PIN pin (stop makeing sound)
	digitalWrite(BUZZER_PIN, HIGH);
	delay(delay_ms);
}

// moving the Robots wheels
// Parameters are a refernce to a Wheels object
void moveWheels(Wheels &wheels)
{
	// Enabling the wheels object
	wheels.enable();
	// Left joyStick for moving the vehicle
	static Joystick lStick(L_STICK_X, L_STICK_Y, L_STICK_Z); 

	// Checking if the joystick is in the dead zone
	if (fabs(lStick.getX()) <= 15.0f && fabs(lStick.getY()) <= 15.0f) 
	{
		// Stop movment from the wheels
		wheels.move(Wheels::Directions::Stop);
		// Disable the wheels so they 
		// wont move accidently
		wheels.disable();
		// Retrun from funciton, stop execution
		return;
	}

	// Edge case for division by zero
	if (lStick.getX() != 0) 
		// Using trigonometry to get the angle of the stick
		angle = sin(lStick.getY() / lStick.getX());
	else
	 	// If the left stick is resting
		// then the angle should be at zero
		float angle = 0.0f;

	// Using the pythagorean theorem to solve for the distance
	// from the center of the joystick to the current position
	float distance = sqrt(fabs(lStick.getY() * lStick.getY()) + fabs(lStick.getX() * lStick.getX()));

	// Moveing the robot according to the angle
	if (angle <= 90.0f)
		wheels.move(Wheels::Directions::Right);		// Right
	else if (angle <= 180.0f)
		wheels.move(Wheels::Directions::Forward);	// Forwards
	else if (angle <= 270.0f)
		wheels.move(Wheels::Directions::Left);		// Left
	else
		wheels.move(Wheels::Directions::Backwords); // Backwards

	// Disable the wheels so they
	// wont move accidently
	wheels.disable();
}
