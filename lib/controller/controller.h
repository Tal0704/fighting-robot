#pragma once
#include "../pins.h"
#include "../joystick/Joystick.h"

class Controller
{
protected:
	Joystick lStick;
	Joystick rStick;

	enum interface
	{
		controller = 0,
		application
	};
};