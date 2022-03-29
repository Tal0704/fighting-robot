#include <inc.h>
#include <firebaseInit.h>
#include <laser.h>
#include <vector.h>
#include <misc.h>
#include <servo.h>

void setup()
{
	Serial.begin(9600);
	Serial.println();
	initMotors();
	for (size_t i = 0; i < 5; i++)
	{
		delay(500);
	}
	

	firebase::init(WIFI_NAME_COLLEGE, WIFI_PASS_COLLEGE, doGetFb);
	laser::init();
	servo::init();
}

void loop()
{
	// if(laser::isHit())
	// 	Firebase.setIntAsync(firebase::fbdata, "processor/isHit", true);
	// else
	// 	Firebase.setIntAsync(firebase::fbdata, "processor/isHit", false);

	Firebase.setIntAsync(firebase::fbdata, "processor/isHit", laser::isHit() ? true : false);

}

// void setup()
// {
// 	ESP32PWM::allocateTimer(0);
// 	ESP32PWM::allocateTimer(1);
// 	ESP32PWM::allocateTimer(2);
// 	ESP32PWM::allocateTimer(3);
// 	ser.setPeriodHertz(50);
// 	ser.attach(18, 500, 2400);
// }

// void loop()
// {
// 	for (size_t i = 0; i < 180; i++)
// 	{
// 		ser.write(i);
// 		delay(5);
// 	}
// 	for (size_t i = 180; i >= 1; i--)
// 	{
// 		ser.write(i);
// 		delay(5);
// 	}
// 	Serial.println("finished");
// }