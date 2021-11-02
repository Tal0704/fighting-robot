#include "Joystick.h"

Joystick::Joystick(unsigned int x, unsigned int y, unsigned int z)
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;

    pinMode(this->pos.x, INPUT);
    pinMode(this->pos.y, INPUT);
    pinMode(this->pos.z, INPUT);
}