#include <preprocess.h>

FirebaseData fbdata;

void setup()
{
	Serial.begin(9600);
	WiFi.begin(WIFI_NAME_COLLEGE, WIFI_PASS_COLLEGE);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println(WiFi.localIP());

	Firebase.begin(FB_URL, FB_KEY);
}

void loop()
{
	
}
