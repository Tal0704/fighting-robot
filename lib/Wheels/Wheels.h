#pragma once
#include <inc.h>
#include <math.h>

// motors[0] = Upper right
// motors[1] = Lower right
// motors[2] = Lower left
// motors[3] = Upper left

// left  = +
// right = -

class Wheels
{
private:
	pin m_motors[4];
	unsigned int m_enable;

	void stop(const pin&);
	void forwards(const pin&, float speed);
	void backwards(const pin&);

public:
	Wheels();

	enum Direction
	{
		Backwords = 0,
		Forward,
		Right,
		Left,
		Stop
	};

	void enable() { digitalWrite(this->m_enable, HIGH); }
	void disable() { digitalWrite(this->m_enable, LOW); }
	void move(float angle, float speed);
};
