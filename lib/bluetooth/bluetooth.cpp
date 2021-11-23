#include "bluetooth.h"

Vector getJoystickData(const Joystick&)
{
	std::string data = "";
	if(btRecive.available())
		data = btRecive.readString();
	if(data != "")
	{
		
	}
	return Vector();
}

