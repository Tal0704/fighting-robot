#pragma once
#include <inc.h>
#include <firebase.h>

void initFirebase(const char *wifiName, const char *wifiPass, FirebaseData::StreamEventCallback callback);

void setFirebaseCallback(FirebaseData::StreamEventCallback callback);