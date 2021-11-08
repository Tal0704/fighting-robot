#include <Arduino.h>
#include "../pins.h"

// Active low
namespace laser
{
    bool isHit()
    {
        return !digitalRead(LASER_RECIVE);
    }

    void emit()
    {
        digitalWrite(LASER_EMIT, LOW);
    }

    void stopEmitting()
    {
        digitalWrite(LASER_EMIT, HIGH);
    }

	void init()
	{
		pinMode(LASER_RECIVE, INPUT);
		pinMode(LASER_EMIT, OUTPUT);
	}
};
