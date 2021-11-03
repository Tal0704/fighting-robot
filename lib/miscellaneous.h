#include <Arduino.h>
#include <math.h>
#include "joystick/Joystick.h"
#include "MotorDC/MotorDC.h"
#include "pins.h"

unsigned int getDistance();

// Active low
void buzz(unsigned int delay_ms);

void moveWheels(MotorDC &motor);