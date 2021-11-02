#pragma once
#include <Arduino.h>
#include "pos.h"

class Joystick
{
private:
    Position pos;
public:
    Joystick() = delete;

    Joystick(unsigned int x, unsigned int y, unsigned int z);

    float getX()  { return analogRead(this->pos.x);  }
    float getY()  { return analogRead(this->pos.y);  }
    short getZ()  { return digitalRead(this->pos.z); }
};