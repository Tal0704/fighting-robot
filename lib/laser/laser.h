#pragma once
#include <inc.h>
// Creating a wrapper for laser
// so that the call for the 
// functions are clearer
namespace laser
{
	// Returning if the robot has been heat
    bool isHit()
    {
		// Returning the complimant of
		// the logic value that is in 
		// the pin LASER_RECIVE
        return !digitalRead(LASER_RECIVE);
    }

	// Shoot the laser from the robot
    void emit()
    {
		// Output '0' to LASER_EMIT pin
        digitalWrite(LASER_EMIT, LOW);
    }

	// Stop shooting laser from robot
    void stopEmitting()
    {
		// Output '1' to LASER_EMIT pin
        digitalWrite(LASER_EMIT, HIGH);
    }

	// Initialize the laser
	void init()
	{
		pinMode(LASER_RECIVE, INPUT);
		pinMode(LASER_EMIT, OUTPUT);
	}
};
