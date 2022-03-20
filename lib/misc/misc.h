#pragma once
#include <Arduino.h>
#include <math.h>
#include "../joystick/Joystick.h"
#include "../Wheels/Wheels.h"
#include "../pins.h"

unsigned int getDistance();

// Active low
void buzz(unsigned int delay_ms);

void initFirebase(const char *wifiName, const char *wifiPass);