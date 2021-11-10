#include "input.h"

void Input::moveWheels(Wheels& wheels)
{
	wheels.enable();
	
	if (fabs(this->lStick.getX()) <= 15.0f && fabs(this->lStick.getY()) <= 15.0f) // Checking if the joystick is in the dead zone
	{
		wheels.move(Wheels::Directions::Stop);
		wheels.disable();
		return;
	}

	if (this->lStick.getX() != 0) // Stopping div by zero
		// Using sin to get the angle of the stick
		this->input.angle = sin(this->lStick.getY() / this->lStick.getX());
	else
		this->input.angle = 0.0f;

	// Using the pythagorean theorem to solve for the amount that was pushed
	this->input.amount = sqrt(fabs(this->lStick.getY() * this->lStick.getY()) + fabs(this->lStick.getX() * this->lStick.getX()));

	if (this->input.angle <= 90.0f)
		wheels.move(Wheels::Directions::Right); // Right
	else if (this->input.angle <= 180.0f)
		wheels.move(Wheels::Directions::Forward); // Forwards
	else if (this->input.angle <= 270.0f)
		wheels.move(Wheels::Directions::Left); // Left
	else
		wheels.move(Wheels::Directions::Backwords); // Backwards

	wheels.move(Wheels::Directions::Stop);
	wheels.disable();
}

void Input::getInputController()
{
	
}