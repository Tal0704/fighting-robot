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
	servo::init();
	// initializing servo
	servo::horizontal.write(90);
	Serial.printf("Servo is in pos: %d\n", servo::horizontal.read());
	// initializing firebase with wifi name, password and callback function
	firebase::init(WIFI_NAME_HOME, WIFI_PASS_HOME, doGetFb);
}

void loop()
{
	// if the robot is hit, send tru to firebase otherwise send false to firebase
	Firebase.setIntAsync(firebase::fbdata, "processor/isHit", laser::isHit() ? true : false);
}