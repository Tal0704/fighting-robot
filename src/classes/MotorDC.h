#pragma once
#include <Arduino.h>
#include "../pins.h"

class MotorDC
{
private:
	unsigned int m_pin1;
	unsigned int m_pin2;
	unsigned int m_enable;

public:
	MotorDC(unsigned int pin1, unsigned int pin2, unsigned int enable);
	
	enum class Directions { Backwords = 1, Stop, Forward };

	void enable() { digitalWrite(this->m_enable, HIGH); }
	void disable() { digitalWrite(this->m_enable, LOW); }
	void move(Directions dir);
};