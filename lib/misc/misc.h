#pragma once
#include <inc.h>
#include <math.h>
#include <WiFi.h>
#include <servo.h>
#include <firebaseInit.h>
#include <Firebase.h>
#include <vector.h>
#include <laser.h>
#include <Wheel.h>
#include <unordered_map>

unsigned int getDistance();

// Active low
void buzz(unsigned int delay_ms);

void doGetFb(StreamData data);

inline void initMotors();

void initServo();