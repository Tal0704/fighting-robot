#include "Wheel.h"

// std::once_flag initFrequencyWheels;

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

	// std::call_once(initFrequencyWheels, [&](){
	// 	analogWriteFrequency(MOTOR_EN, 10e3);
	// });
}

Wheel::Wheel()
{
	this->m_motor.forwards = 0;
	this->m_motor.backwards = 0;
	this->m_enable = 0;
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

void Wheel::setPWM(double precent) const
{
	precent = precent * 2.5;
	analogWrite(this->m_enable, precent);
}
