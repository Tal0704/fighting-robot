#include <inc.h>
#include <firebaseInit.h>
#include <laser.h>
#include <vector.h>
#include <misc.h>
#include <servo.h>

void setup()
{
	Serial.begin(9600);

	firebase::init(WIFI_NAME_HOME, WIFI_PASS_HOME, doGetFb);
	laser::init();
	// initServo();
	initMotors();
}

void loop()
{
	// if(laser::isHit())
	// 	Firebase.setIntAsync(firebase::fbdata, "processor/isHit", true);
	// else
	// 	Firebase.setIntAsync(firebase::fbdata, "processor/isHit", false);

	// if(firebase::input::isShooting)
	// 	digitalWrite(LASER_EMIT, HIGH);

	using namespace firebase::input;
	if(leftStick.strength > 0)
	{ 
		if(leftStick.angle > 45 && leftStick.angle < 135)
		{
			digitalWrite(LEFT_TOP_WHEEL, HIGH);
			digitalWrite(RIGHT_TOP_WHEEL, HIGH);
			digitalWrite(LEFT_BOTTOM_WHEEL, LOW);
			digitalWrite(RIGHT_BOTTOM_WHEEL, LOW);
			Serial.println("Top");
		}
		else if(leftStick.angle > 135 && leftStick.angle < 225)
		{
			digitalWrite(LEFT_TOP_WHEEL, LOW);
			digitalWrite(RIGHT_TOP_WHEEL, HIGH);
			digitalWrite(LEFT_BOTTOM_WHEEL, LOW);
			digitalWrite(RIGHT_BOTTOM_WHEEL, HIGH);
			Serial.println("Left");
		}
		else if(leftStick.angle > 225 && leftStick.angle < 315)
		{
			digitalWrite(LEFT_TOP_WHEEL, LOW);
			digitalWrite(RIGHT_TOP_WHEEL, LOW);
			digitalWrite(LEFT_BOTTOM_WHEEL, HIGH);
			digitalWrite(RIGHT_BOTTOM_WHEEL, HIGH);
			Serial.println("Bottom");
		}
		else if(leftStick.angle > 315 || leftStick.angle < 45)
		{
			digitalWrite(LEFT_TOP_WHEEL, HIGH);
			digitalWrite(RIGHT_TOP_WHEEL, LOW);
			digitalWrite(LEFT_BOTTOM_WHEEL, HIGH);
			digitalWrite(RIGHT_BOTTOM_WHEEL, LOW);
			Serial.println("Right");
		}
	}
}

// void setup()
// {
// 	ESP32PWM::allocateTimer(0);
// 	ESP32PWM::allocateTimer(1);
// 	ESP32PWM::allocateTimer(2);
// 	ESP32PWM::allocateTimer(3);
// 	ser.setPeriodHertz(50);
// 	ser.attach(18, 500, 2400);
// }

// void loop()
// {
// 	for (size_t i = 0; i < 180; i++)
// 	{
// 		ser.write(i);
// 		delay(5);
// 	}
// 	for (size_t i = 180; i >= 1; i--)
// 	{
// 		ser.write(i);
// 		delay(5);
// 	}
// 	Serial.println("finished");
// }