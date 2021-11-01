#include <Arduino.h>
#include <ESP32Servo.h>

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
        se.write(0);
    }
}