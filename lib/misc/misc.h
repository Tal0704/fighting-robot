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
 
unsigned int getDistance();

// Active low
void buzz(unsigned int delay_ms);

Vector convertPolarToCartezian(const Vector &vect);

void doGetFb(StreamData data);

void initMotors();