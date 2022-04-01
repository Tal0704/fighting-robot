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
	// beggining the wifi of the rorbot
	WiFi.begin(wifiName, wifiPass);

	Serial.print("Connecting to wifi");

	// while not conectted try to conect
	while(WiFi.status() != WL_CONNECTED)
	{
		delay(300);
		Serial.print(".");
	}

	// begin the firebase on the right link and key 
	// for the authentication so firebase knows we
	// have premission to read and change any data
	Firebase.begin(FB_URL, FB_KEY);
 
	// telling the listener to listen to the processor branch
	if(!Firebase.beginStream(firebase::fbdata, "processor"))
		// if an error occurred, print the reason
		Serial.printf("Stream begin error, %s\n\n", firebase::fbdata.errorReason().c_str());

	// setting the callback function 
	m_callback = callback;

	// starting the listener, user the fbdata variable to store the data
	// and to be the base for the listener, call the m_callback variable
	// when there is a change on the given branch, call doStreamTimeout
	// function when an error has occurred
	Firebase.setStreamCallback(firebase::fbdata, m_callback, doStreamTimeout);
	Serial.println("\nConnected to firebase succefully!");
}

void firebase::setCallback(FirebaseData::StreamEventCallback callback)
{
	m_callback = callback;
	Firebase.setStreamCallback(firebase::fbdata, m_callback, doStreamTimeout);
}
