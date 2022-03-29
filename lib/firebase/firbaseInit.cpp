#include "firebaseInit.h"

static FirebaseData::StreamEventCallback m_callback;
 
void doStreamTimeout(bool timeout)
{
	if(timeout)
		Serial.println("Stream timed out, resuming...\n");

	if(!firebase::fbdata.httpConnected())
		Serial.printf("Error code: %d, reason: %s\n\n", firebase::fbdata.httpCode(), firebase::fbdata.errorReason().c_str());
}

void firebase::init(const char *wifiName, const char *wifiPass, FirebaseData::StreamEventCallback callback)
{
	WiFi.begin(wifiName, wifiPass);

	Serial.print("Connecting to wifi");

	while(WiFi.status() != WL_CONNECTED)
	{
		delay(300);
		Serial.print(".");
	}

	Firebase.begin(FB_URL, FB_KEY);
 
	if(!Firebase.beginStream(firebase::fbdata, "processor"))
		Serial.printf("Stream begin error, %s\n\n", firebase::fbdata.errorReason().c_str());

	m_callback = callback;
	Firebase.setStreamCallback(firebase::fbdata, m_callback, doStreamTimeout);
	Serial.println("\nConnected to firebase succefully!");
}

void firebase::setCallback(FirebaseData::StreamEventCallback callback)
{
	m_callback = callback;
}