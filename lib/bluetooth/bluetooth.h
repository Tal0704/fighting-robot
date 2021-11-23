#pragma once
#include <BluetoothSerial.h>
#include <Joystick.h>
#include <vector.h>
#include <string>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

static BluetoothSerial btRecive;

void btInit()
{
	btRecive.begin("Fighting robot");
}

Vector getJoystickData(const Joystick&);