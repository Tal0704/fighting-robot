#include <math.h>
#include <Arduino.h>
#include "../pins.h"
#include "misc.h"

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

void buzz(unsigned int delay_ms)
{
	digitalWrite(BUZZER_PIN, LOW);
	delay(delay_ms);
	digitalWrite(BUZZER_PIN, HIGH);
	delay(delay_ms);
}

void moveWheels(Wheels &wheels)
{
	wheels.enable();
	static Joystick lStick(L_STICK_X, L_STICK_Y, L_STICK_Z); // Left joyStick for moving the vehicle
	if (fabs(lStick.getX()) <= 15.0f && fabs(lStick.getY()) <= 15.0f) // Checking if the joystick is in the dead zone
	{
		wheels.move(Wheels::Directions::Stop);
		wheels.disable();
		return;
	}

	float angle;
	if (lStick.getX() != 0) // Stopping div by zero
		// Using sin to get the angle of the stick
		angle = sin(lStick.getY() / lStick.getX());
	else
		angle = 0.0f;

	// Using the pythagorean theorem to solve for the amount that was pushed
	// float amount = sqrt(fabs(lStick.getY() * lStick.getY()) + fabs(lStick.getX() * lStick.getX()));

	if (angle <= 90.0f)
		wheels.move(Wheels::Directions::Right); // Right
	else if (angle <= 180.0f)
		wheels.move(Wheels::Directions::Forward); // Forwards
	else if (angle <= 270.0f)
		wheels.move(Wheels::Directions::Left); // Left
	else
		wheels.move(Wheels::Directions::Backwords); // Backwards

	wheels.move(Wheels::Directions::Stop);
	wheels.disable();
}