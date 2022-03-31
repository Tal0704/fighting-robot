#include <inc.h>
#include <firebaseInit.h>
#include <laser.h>
#include <misc.h>
#include <servo.h>

void setup()
{
	// initializing Serial monitor
	Serial.begin(9600);
	Serial.println();
	// initializing motors
	initMotors();
	
	// initializing laser
	laser::init();
	// initializing servo
	servo::init();
	Serial.print("Started writing to servo!\n");
	servo::horizontal.write(90);
	Serial.print("Started writing to servo!\n");
	for (size_t i = 0; i < 10; i++)
	{
		delay(500);
	}
	// initializing firebase with wifi name, password and callback function
	firebase::init(WIFI_NAME_COLLEGE, WIFI_PASS_COLLEGE, doGetFb);
}

void loop()
{
	// if the robot is hit, send tru to firebase otherwise send false to firebase
	Firebase.setIntAsync(firebase::fbdata, "processor/isHit", laser::isHit() ? true : false);
}