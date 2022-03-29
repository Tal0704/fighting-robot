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
	if(laser::isHit())
	{
		Serial.print("hit\n");
		Firebase.setIntAsync(firebase::fbdata, "processor/isHit", true);
	}
	else
	{
		Firebase.setIntAsync(firebase::fbdata, "processor/isHit", false);
		Serial.print("not hit\n");
	}


}