#pragma once
#include <inc.h>
#include <firebase.h>
#include <vector.h>

namespace firebase
{
static FirebaseData fbdata;
 
void init(const char *wifiName, const char *wifiPass, FirebaseData::StreamEventCallback callback);

void setCallback(FirebaseData::StreamEventCallback callback);
 
namespace input
{
static Vector leftStick, rightStick;
}
};