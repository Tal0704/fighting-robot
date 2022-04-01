#include <inc.h>
#include <firebaseInit.h>
#include <laser.h>
#include <misc.h>
#include <servo.h>

void setup()
{
	// initializing firebase with wifi name, password and callback function
	firebase::init(WIFI_NAME_HOME, WIFI_PASS_HOME, doGetFb);
	// initializing Serial monitor
	Serial.println();
	// initializing motors
	initMotors();
	// initializing laser
	laser::init();
	// initializing servo
	servo::init();
}

void loop()
{
	// if the robot is hit, send tru to firebase otherwise send false to firebase
	Firebase.setIntAsync(firebase::fbdata, "processor/isHit", laser::isHit() ? true : false);
}