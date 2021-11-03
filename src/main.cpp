#include "../lib/pins.h"
#include "../lib/MotorDC/MotorDC.h"
#include "../lib/laser/laser.h"
#include "../lib/servo/servo.h"
#include "../lib/miscellaneous.h"
#include "../lib/joystick/Joystick.h"

Joystick joy(L_STICK_X, L_STICK_Y, L_STICK_Z);

void setup()
{
    pinMode(L_STICK_X, INPUT);
    pinMode(L_STICK_Y, INPUT);
    Serial.begin(9600);
}

void loop()
{
    Serial.printf("X: %d\t Y: %d\n", joy.getX(), joy.getY());
}

