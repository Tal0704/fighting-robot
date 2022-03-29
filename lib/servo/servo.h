#pragma once
#include <inc.h>
#include <ESP32Servo.h>

namespace servo
{
static Servo horizontal, vertical;

// void initTime()
// {
// 	ESP32PWM::allocateTimer(0);
// 	ESP32PWM::allocateTimer(1);
// 	// ESP32PWM::allocateTimer(2);
// 	// ESP32PWM::allocateTimer(3);
// }

}
static void initServo()
{
	using namespace servo;
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	horizontal.setPeriodHertz(50);
	horizontal.attach(SERVO_HOR, 500, 2400);
	 
	// ESP32PWM::allocateTimer(0);
	// ESP32PWM::allocateTimer(1);
	// ESP32PWM::allocateTimer(2);
	// ESP32PWM::allocateTimer(3);
	// servo::horizontal.setPeriodHertz(50); // setting up 50 Hz
	// servo::horizontal.attach(SERVO_HOR, 500, 2400);
	// servo::vertical.attach(SERVO_VER, 500, 2400);
	// servo::vertical.write(0);

	Serial.print("Finished initializing servo\n");
}