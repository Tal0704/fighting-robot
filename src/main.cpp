#include <FirebaseESP32.h>
#include <WiFi.h>
#include "macros.h"
#include "../lib/pins.h"
#include "../lib/Wheels/Wheels.h"
#include "../lib/laser/laser.h"
#include "../lib/servo/servo.h"
#include "../lib/misc/misc.h"
#include "../lib/joystick/Joystick.h"

FirebaseData fbdata;

void setup()
{
	// Serial.begin(9600);
	// WiFi.begin(WIFI_NAME_COLLEGE, WIFI_PASS_COLLEGE);
	// while (WiFi.status() != WL_CONNECTED)
	// {
	// 	delay(1000);
	// 	Serial.print(".");
	// }
	// Serial.println("");
	// Serial.println(WiFi.localIP());

	// Firebase.begin(FB_URL, FB_KEY);
}

void loop()
{
	buzz(100);
}
