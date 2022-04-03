#include "laser.h"

bool laser::isHit()
{
	// return the compliment of
	// the state of LASER_RECIVE pin
	return !digitalRead(LASER_RECIVE);
}
 
void laser::emit()
{
	// Output '0' to LASER_EMIT pin
	digitalWrite(LASER_EMIT, LOW);
	
}
 
void laser::stopEmitting()
{
	// Output '1' to LASER_EMIT pin
	digitalWrite(LASER_EMIT, HIGH);
}

void laser::init()
{
	pinMode(LASER_RECIVE, INPUT);
	pinMode(LASER_EMIT, OUTPUT);
	laser::stopEmitting();
}