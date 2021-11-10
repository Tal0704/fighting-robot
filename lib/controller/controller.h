#pragma once
#include "../pins.h"
#include "../joystick/Joystick.h"

class Controller
{
protected:
	Joystick lStick;
	Joystick rStick;
	Controller()
	{
		lStick.construct(L_STICK_X, L_STICK_Y, L_STICK_Z);
		rStick.construct(R_STICK_X, R_STICK_Y, R_STICK_Z);
	}
};