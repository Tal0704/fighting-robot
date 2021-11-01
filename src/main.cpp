#include <ESP32Servo.h>
#include "pins.h"
#include "classes/MotorDC.h"

// TODO: fix servo angle

// Active low
namespace laser
{
    bool isHit()
    {
        return !digitalRead(LASER_RECIVE);
    }

    void emit()
    {
        digitalWrite(LASER_EMIT, LOW);
    }

    void stopEmitting()
    {
        digitalWrite(LASER_EMIT, HIGH);
    }
};

namespace servo
{
    void initTime()
    {
        ESP32PWM::allocateTimer(0);
        ESP32PWM::allocateTimer(1);
        ESP32PWM::allocateTimer(2);
        ESP32PWM::allocateTimer(3);
    }

    void init(Servo &se, unsigned int pin)
    {
        se.setPeriodHertz(50); // setting up 50 Hz
        se.attach(pin, 500, 2400);
    }
}

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

// Active low
void buzz(unsigned int delay_ms)
{
    digitalWrite(BUZZER_PIN, LOW);
    delay(delay_ms);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(delay_ms);
}

MotorDC motor(12, 13, 14);

void setup()
{
    
}

void loop()
{

}