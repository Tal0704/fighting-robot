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
	
	// initializing firebase with wifi name, password and callback function
	firebase::init(WIFI_NAME_COLLEGE, WIFI_PASS_COLLEGE, doGetFb);
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