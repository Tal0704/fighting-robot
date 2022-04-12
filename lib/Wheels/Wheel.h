#pragma once
#include <inc.h>
#include <math.h>
#include <MotorPins.h>
#include <mutex>
#include <analogWrite.h>

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
	pin m_enable;

public:
	Wheel();
	Wheel(pin forwards, pin backwards, pin enable);

	void forwards() const;
	void backwards() const;
	void setPWM(const double precent) const;
};
