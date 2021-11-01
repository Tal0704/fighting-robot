#include <ESP32Servo.h>

#define BUZZER_PIN 0

#define TRIG 0
#define ECHO 0

#define LASER_RECIVE 0
#define LASER_EMIT 0

#define SERVO_1 0

// TODO: fix servo angle

class MotorDC
{
private:
    unsigned int m_pin1;
    unsigned int m_pin2;
    unsigned int m_enable;

public:
    MotorDC(unsigned int pin1, unsigned int pin2, unsigned int enable)
        : m_pin1(pin1), m_pin2(pin2), m_enable(enable)
    {
        pinMode(this->m_enable, INPUT);
        pinMode(this->m_pin1, OUTPUT);
        pinMode(this->m_pin2, OUTPUT);

        this->enable();
    }

    enum class Directions
    {
        Backwords = 1,
        Stop,
        Forward
    };

    void enable()
    {
        digitalWrite(this->m_enable, HIGH);
    }

    void disable()
    {
        digitalWrite(this->m_enable, LOW);
    }

    void move(Directions dir)
    {
        switch (dir)
        {
        case Directions::Backwords:
            digitalWrite(this->m_pin1, HIGH);
            digitalWrite(this->m_pin2, LOW);
            break;

        case Directions::Stop:
            digitalWrite(this->m_pin1, LOW);
            digitalWrite(this->m_pin2, LOW);
            break;

        case Directions::Forward:
            digitalWrite(this->m_pin1, LOW);
            digitalWrite(this->m_pin2, HIGH);
            break;
        }
    }
};

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

Servo myServo;

void setup()
{
    
}

void loop()
{

}