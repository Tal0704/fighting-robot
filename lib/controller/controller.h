#pragma once
#include "../pins.h"
#include "../joystick/Joystick.h"

// creating Class for 
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
