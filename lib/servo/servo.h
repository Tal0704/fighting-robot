#pragma once
#include <inc.h>
#include <ESP32Servo.h>

namespace servo
{
static Servo horizontal, vertical;

void init();

}