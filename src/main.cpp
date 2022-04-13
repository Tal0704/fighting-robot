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

	// initializing laser
	laser::init();

	// initializing firebase with wifi name, password and callback function
	firebase::init(WIFI_NAME_HOME, WIFI_PASS_HOME, doGetFb);
	
	// initializing servo
	initServo();

	pinMode(BUZZER_PIN, OUTPUT);

	buzz(250);
}

void loop()
{
	// if the robot is hit, send true to firebase otherwise send false to firebase
	if (laser::isHit())
	{
		Firebase.setIntAsync(firebase::fbdata, "processor/isHit",true);
		digitalWrite(BUZZER_PIN, LOW);
		// Serial.println("Robot got hit!");
	}
	else
	{
		Firebase.setIntAsync(firebase::fbdata, "processor/isHit", false);
		digitalWrite(BUZZER_PIN, HIGH);
	}
}