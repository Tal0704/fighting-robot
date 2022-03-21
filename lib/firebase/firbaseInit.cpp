#include "firebaseInit.h"

static FirebaseData::StreamEventCallback m_callback;
static FirebaseData stream;
 
void doStreamTimeout(bool timeout)
{
	if(timeout)
		Serial.println("Stream timed out, resuming...\n");

	if(!stream.httpConnected())
		Serial.printf("Error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}

void initFirebase(const char* wifiName, const char* wifiPass, FirebaseData::StreamEventCallback callback)
{
	Firebase.begin(FB_URL, FB_KEY);
	WiFi.begin(wifiName, wifiPass);

	while(WiFi.status() != WL_CONNECTED)
	{
		delay(300);
		Serial.print(".");
	}
 
	if(!Firebase.beginStream(stream, "processor/controller/leftStick"))
		Serial.printf("Stream begin error, %s\n\n", stream.errorReason().c_str());

	m_callback = callback;
	Firebase.setStreamCallback(stream, m_callback, doStreamTimeout);
}

void setFirebaseCallback(FirebaseData::StreamEventCallback callback)
{
	m_callback = callback;
}