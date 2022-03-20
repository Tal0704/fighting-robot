#include "Wheels.h"

// Constructor, when the 
// object is first initialized
// the code below is executed
Wheels::Wheels()
{
	// Setting the enable pin for the
	// current object to output
	pinMode(this->m_enable, OUTPUT);
	// For each motor setting the 
	// enable pin to output
	for (MotorPins& motor : this->m_motors)
	{
		pinMode(motor.pin1, OUTPUT);
		pinMode(motor.pin2, OUTPUT);
	}
	// Disabling the wheels so
	// they wont move accidentally
	this->disable();
}

// stopping the specified wheel
void Wheels::stop(MotorPins &motor)
{
	digitalWrite(motor.pin1, LOW);
	digitalWrite(motor.pin2, LOW);
}

// moving forwards the specified wheel
void Wheels::forwards(MotorPins &motor)
{
	digitalWrite(motor.pin1, LOW);
	digitalWrite(motor.pin2, HIGH);
}

// moving backwords the specified wheel
void Wheels::backwards(MotorPins &motor)
{
	digitalWrite(motor.pin1, HIGH);
	digitalWrite(motor.pin2, LOW);
}

void Wheels::move(Wheels::Direction dir)
{
	// Checking what the direction we need to 
	// turn the wheels
	switch (dir)
	{
	// If backwords
	case Direction::Backwords:
		// itterate through all the motors
		for (MotorPins& motor : this->m_motors)
			// Move backwords
			this->backwards(motor);
		// Return from the function
		return;

	// If Forwards
	case Direction::Forward:
		// itterate through all the motors
		for (MotorPins& motor : this->m_motors)
			// Move forwads
			this->forwards(motor);
		// Return from function
		return;

	// If Right
	case Direction::Right:
		for (int i = 0; i < 2; i++)
		{
			// Move the right wheels back
			this->backwards(this->m_motors[i]);
			// And the left wheels forwards
			this->forwards(this->m_motors[4 - 1 - i]);
		}
		// Making the robot move right
		// Return from function
		return;

	// If left
	case Direction::Left:
		for (int i = 0; i < 2; i++)
		{
			// Move the right wheels forwards
			this->forwards(this->m_motors[i]);
			// Move the left wheels back
			this->backwards(this->m_motors[4 - 1 - i]);
		}
		// Making the robot move left
		// Return from function
		return;

	// If stop
	case Direction::Stop:
		// Itterate through all the motors
		for (MotorPins& motor : this->m_motors)
			// Stop all the motors
			this->stop(motor);
		// Return from function
		return;
	}
}
