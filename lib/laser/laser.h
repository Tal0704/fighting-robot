#pragma once
#include <inc.h>
#include <firebaseInit.h>
#include <soc/rtc_wdt.h>

bool isGameOver = false;

void IRAM_ATTR isr()
{
	Firebase.setIntAsync(firebase::fbdata, "/processor/laserEmitter", 1);
	// Serial.println("Laser Hit!");
}

// Creating a wrapper for laser
// so that the call for the 
// functions are clearer
namespace laser
{
	bool isHit()
	{
		// return the compliment of
		// the state of LASER_RECIVE pin
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

	// Initialize the lasers
	void init()
	{
		pinMode(LASER_RECIVE, INPUT_PULLUP);
		pinMode(LASER_EMIT, OUTPUT);
	}
};
