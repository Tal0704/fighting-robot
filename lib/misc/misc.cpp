#include <math.h>
#include <Arduino.h>
#include <WiFi.h>
#include <Firebase.h>
#include "misc.h"
#include "../pins.h"
#include "../../src/preprocess.h"

unsigned int getDistance()
{
	long duration;

	// start of waking call for the sensor
	digitalWrite(TRIG, LOW);
	delayMicroseconds(2);

	// end of waking call for the sensor
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);

	// sending a signal and seeing the
	// duration that it takes to get back
	digitalWrite(TRIG, LOW);
	duration = pulseIn(ECHO, HIGH);

	// returning the distance in cm
	return duration / 29 / 2;
}

void buzz(unsigned int delay_ms)
{
	digitalWrite(BUZZER_PIN, LOW);
	delay(delay_ms);
	digitalWrite(BUZZER_PIN, HIGH);
	delay(delay_ms);
}

void initFirebase()
{
	WiFi.begin(WIFI_NAME_HOME, WIFI_PASS_HOME);
	while (WiFi.status() != WL_CONNECTED)
	{
#if defined(_DEBUG)
		Serial.printf("wifi\n");
#endif // _DEBUG
		delay(1000);
	}
#if defined(_DEBUG)
	Serial.printf("\nConnected!\n");
#endif // _DEBUG
	Firebase.begin(FB_URL, FB_KEY);
}