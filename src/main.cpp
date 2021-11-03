#include <preprocess.h>

FirebaseData fbdata;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(WIFI_NAME_HOME, WIFI_PASS_HOME);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\n");
    Serial.print(WiFi.localIP());

    Firebase.begin(FB_URL, FB_KEY);

    Firebase.setInt(fbdata, "/s1", 10);
}

void loop()
{
    
}

