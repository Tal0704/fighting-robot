#include <FirebaseESP32.h>
#include <WiFi.h>
#include "../lib/pins.h"
#include "../lib/MotorDC/MotorDC.h"
#include "../lib/laser/laser.h"
#include "../lib/servo/servo.h"
#include "../lib/miscellaneous.h"
#include "../lib/joystick/Joystick.h"

#define WIFI_NAME_COLLEGE "Kinneret College"
#define WIFI_PASS_COLLEGE ""

#define WIFI_NAME_HOME "CTS-3BC4-WIFI-5GHz"
#define WIFI_PASS_HOME "000619383BC4"

#define FB_KEY "3j9D3xsWGfxxkIbYxfCzu75zMfM8Czbawt2pHF47"
#define FB_URL "fighting-robot-5ba4e-default-rtdb.firebaseio.com"