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
	firebase::init(WIFI_NAME_COLLEGE, WIFI_PASS_COLLEGE, doGetFb);
	
	// initializing servo
	initServo();

	pinMode(BUZZER_PIN, OUTPUT);

	buzz(500);
}

void loop()
{
	// if the robot is hit, send true to firebase otherwise send false to firebase
	if (laser::isHit())
	{
		Firebase.setBoolAsync(firebase::fbdata, "processor/isHit",true);
		digitalWrite(BUZZER_PIN, LOW);
		// Serial.println("Robot got hit!");
	}
	else
	{
		Firebase.setBoolAsync(firebase::fbdata, "processor/isHit", false);
		digitalWrite(BUZZER_PIN, HIGH);
	}
}