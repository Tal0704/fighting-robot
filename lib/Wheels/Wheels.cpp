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

void Wheels::move(Wheels::Directions dir)
{
	switch (dir)
	{
	case Directions::Backwords:
		for (MotorPins motor : this->m_motors)
			this->backwards(motor);
		return;

	case Directions::Forward:
		for (MotorPins motor : this->m_motors)
			this->forwards(motor);
		return;

	case Directions::Right:
		for (int i = 0; i < 2; i++)
		{
			this->backwards(this->m_motors[i]);
			this->forwards(this->m_motors[4 - 1 - i]);
		}
		
		return;

	case Directions::Left:
		for (int i = 0; i < 2; i++)
		{
			this->forwards(this->m_motors[i]);
			this->backwards(this->m_motors[4 - 1 - i]);
		}
		return;

	case Directions::Stop:
		for (MotorPins motor : this->m_motors)
			this->stop(motor);
		return;
	}
}
