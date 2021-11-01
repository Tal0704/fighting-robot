#include "MotorDC.h"

MotorDC::MotorDC(unsigned int pin1, unsigned int pin2, unsigned int enable)
    : m_pin1(pin1), m_pin2(pin2), m_enable(enable)
{
    pinMode(this->m_enable, INPUT);
    pinMode(this->m_pin1, OUTPUT);
    pinMode(this->m_pin2, OUTPUT);

    this->enable();
}

void MotorDC::move(MotorDC::Directions dir)
{
    switch (dir)
    {
    case Directions::Backwords:
        digitalWrite(this->m_pin1, HIGH);
        digitalWrite(this->m_pin2, LOW);
        break;

    case Directions::Stop:
        digitalWrite(this->m_pin1, LOW);
        digitalWrite(this->m_pin2, LOW);
        break;

    case Directions::Forward:
        digitalWrite(this->m_pin1, LOW);
        digitalWrite(this->m_pin2, HIGH);
        break;
    }
}