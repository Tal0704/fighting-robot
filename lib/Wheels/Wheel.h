#pragma once
#include <inc.h>
#include <math.h>
#include <MotorPins.h>

// motors[0] = Upper right
// motors[1] = Lower right
// motors[2] = Lower left
// motors[3] = Upper left

// left  = +
// right = -

class Wheel
{
private:
	MotorPins m_motor;
	unsigned int m_enable;

	Wheel();

public:
	Wheel(pin forwards, pin backwards);

	void stop();
	void forwards();
	void backwards();
	inline void enable() { digitalWrite(this->m_enable, HIGH); }
	inline void disable() { digitalWrite(this->m_enable, LOW); }
};
