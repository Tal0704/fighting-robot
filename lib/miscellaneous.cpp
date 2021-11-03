#include <Arduino.h>
#include "pins.h"
#include "miscellaneous.h"

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

void moveWheels(MotorDC &motor)
{
    Joystick lStick(L_STICK_X, L_STICK_Y, L_STICK_Z);
    float angle = sin(lStick.getY() / lStick.getX()); // edge case for div by zero
    float amount = sqrt(lStick.getY() * lStick.getY() + lStick.getX() * lStick.getX());
}