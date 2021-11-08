#pragma once
#include <Arduino.h>
#include "../pins.h"
#include "MotorPins.h"

// motors[0] = Upper right
// motors[1] = Lower right
// motors[2] = Lower left
// motors[3] = Upper left

class Wheels
{
private:
	MotorPins m_motors[4];
	unsigned int m_enable;

	void stop(MotorPins&);
	void forwards(MotorPins &);
	void backwards(MotorPins&);

public:
	Wheels();

	enum class Directions
	{
		Backwords = 1,
		Forward,
		Right,
		Left,
		Stop
	};

	void enable() { digitalWrite(this->m_enable, HIGH); }
	void disable() { digitalWrite(this->m_enable, LOW); }
	void move(Directions dir);
};