#include "Wheel.h"

std::once_flag initFrequencyWheels;

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

	std::call_once(initFrequencyWheels, [&]() {
		ledcSetup(5, 5000, 8);
		ledcAttachPin(MOTOR_EN, 5);
	});
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
	#define DC precent * 2.5

	ledcSetup(5, 5e3, 8);
	ledcWrite(5, DC);
	#if false
	Serial.print("D.C for wheels is: ");
	Serial.println(ledcRead(5));
	Serial.print("Frequeny for wheels is: ");
	Serial.println(ledcReadFreq(5));
	#endif
}

void Wheel::stop() const
{
	digitalWrite(this->m_motor.backwards, LOW);
	digitalWrite(this->m_motor.forwards, LOW);
}