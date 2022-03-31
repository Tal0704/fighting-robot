#include "servo.h"
 
void servo::init()
{
	Serial.println("Initializing servo");
	using namespace servo;
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	horizontal.setPeriodHertz(50);
	horizontal.attach(18, 500, 2400);

	vertical.setPeriodHertz(50);
	vertical.attach(SERVO_VER, 500, 2400);
	 

	Serial.print("Finished initializing servo\n");
}