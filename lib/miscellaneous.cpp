#include <math.h>
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

    if (fabs(lStick.getX()) <= 15.0f && fabs(lStick.getY()) <= 15.0f)
    {
        motor.move(MotorDC::Directions::Stop);
        return;
    }
    float angle;
    if (lStick.getX() != 0) // Stopping divding by zero
        angle = sin(lStick.getY() / lStick.getX());
    else
        angle = 0.0f;
    
    float amount = sqrt(fabs(lStick.getY() * lStick.getY()) + fabs(lStick.getX() * lStick.getX()));

    if (angle <= 90.0f)
        motor.move(MotorDC::Directions::Backwords); // Right
    else if (angle <= 180.0f)
        motor.move(MotorDC::Directions::Forward); // Forwards
    else if (angle <= 270.0f)
        motor.move(MotorDC::Directions::Backwords); // Left
    else
        motor.move(MotorDC::Directions::Backwords); // Backwards
}