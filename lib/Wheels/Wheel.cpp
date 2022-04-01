#include "Wheel.h"
 
#define CHANNEL 0
#define FREQ 5000

// Constructor:
//  when the object is first initialized
// the code below is executed
Wheel::Wheel(pin forwards, pin backwards)
{
	// Assigning each motor with it's respective pin
	this->m_motor.forwards = forwards;
	this->m_motor.backwards = backwards;

	// Setting the enable pin for the
	// current object to output
	pinMode(this->m_enable, OUTPUT);
	 
	// enableing the pins of the motor as output
	pinMode(this->m_motor.forwards, OUTPUT);
	pinMode(this->m_motor.backwards, OUTPUT);

	// Disabling the wheels so
	// they wont move accidentally
	this->stop();
	this->disable();
}

// stopping the specified wheel
void Wheel::stop()
{
	digitalWrite(this->m_motor.forwards, LOW);
	digitalWrite(this->m_motor.backwards, LOW);
}

// moving forwards the specified wheel
void Wheel::forwards()
{
	digitalWrite(this->m_motor.forwards, HIGH);
	digitalWrite(this->m_motor.backwards, LOW);
}

// moving backwords the specified wheel
void Wheel::backwards()
{
	digitalWrite(this->m_motor.forwards, LOW);
	digitalWrite(this->m_motor.backwards, HIGH);
}