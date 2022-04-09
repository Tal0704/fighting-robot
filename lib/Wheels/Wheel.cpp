#include "Wheel.h"
 
#define CHANNEL 0
#define FREQ 5000

// Constructor:
//  when the object is first initialized
// the code below is executed
Wheel::Wheel(pin forwards, pin backwards, pin enable)
{
	// Assigning each motor with it's respective pin
	this->m_motor.forwards = forwards;
	this->m_motor.backwards = backwards;
	this->m_enable = enable;

	// Setting the enable pin for the
	// current object to output
	pinMode(this->m_enable, OUTPUT);
	 
	// setting the pins of the motor as output
	pinMode(this->m_motor.forwards, OUTPUT);
	pinMode(this->m_motor.backwards, OUTPUT);
}

Wheel::Wheel()
{
	this->m_motor.forwards = 0;
	this->m_motor.backwards = 0;
	this->m_enable = 0;
}

// stopping the specified wheel
void Wheel::stop() const
{
	digitalWrite(this->m_motor.forwards, LOW);
	digitalWrite(this->m_motor.backwards, LOW);
}

// moving forwards the specified wheel
void Wheel::forwards() const
{
	digitalWrite(this->m_motor.forwards, HIGH);
	digitalWrite(this->m_motor.backwards, LOW);
}

// moving backwords the specified wheel
void Wheel::backwards() const
{
	digitalWrite(this->m_motor.forwards, LOW);
	digitalWrite(this->m_motor.backwards, HIGH);
}