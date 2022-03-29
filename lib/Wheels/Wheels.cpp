#include "Wheels.h"
 
#define CHANNEL 0
#define FREQ 5000

// Constructor:
//  when the object is first initialized
// the code below is executed
Wheels::Wheels()
{
	// Assigning each motor with it's respective pin
	this->m_motors[0] = RIGHT_TOP_WHEEL;
	this->m_motors[1] = RIGHT_BOTTOM_WHEEL;
	this->m_motors[2] = LEFT_BOTTOM_WHEEL;
	this->m_motors[3] = LEFT_TOP_WHEEL;

	// Setting the enable pin for the
	// current object to output
	pinMode(this->m_enable, OUTPUT);
	 
	// For each motor setting the 
	// enable pin to output
	for (const pin& motor : this->m_motors)
	{
		ledcSetup(CHANNEL, FREQ, 8);
		ledcAttachPin(motor, CHANNEL);
	}
	// Disabling the wheels so
	// they wont move accidentally
	this->disable();
}

// stopping the specified wheel
void Wheels::stop(const pin& motor)
{
	for(const pin& motor: this->m_motors)
		ledcWrite(motor, 0);
}

// moving forwards the specified wheel
void Wheels::forwards(const pin& motor, float speed)
{
	float dutyCycle = speed * 12.8;
	for(const pin& motor: this->m_motors)
		ledcWrite(motor, dutyCycle);
}

// moving backwords the specified wheel
void Wheels::backwards(const pin& motor)
{
}

void Wheels::move(float angle, float speed)
{
	float x, y;

	x = speed * cosf(angle);
	y = speed * sinf(angle);

	// // Checking what the direction we need to 
	// // turn the wheels
	// switch (angle) {
	// // If backwords
	// case 90.0f:
	// 	// itterate through all the motors
	// 	for (pin& motor : this->m_motors)
	// 		// Move backwords
	// 		this->backwards(motor);
	// 	// Return from the function
	// 	return;

	// // If Forwards
	// case Direction::Forward:
	// 	// itterate through all the motors
	// 	for (pin& motor : this->m_motors)
	// 		// Move forwads
	// 		this->forwards(motor);
	// 	// Return from function
	// 	return;

	// // If Right
	// case Direction::Right:
	// 	for (int i = 0; i < 2; i++)
	// 	{
	// 		// Move the right wheels back
	// 		this->backwards(this->m_motors[i]);
	// 		// And the left wheels forwards
	// 		this->forwards(this->m_motors[4 - 1 - i]);
	// 	}
	// 	// Making the robot move right
	// 	// Return from function
	// 	return;

	// // If left
	// case Direction::Left:
	// 	for (int i = 0; i < 2; i++)
	// 	{
	// 		// Move the right wheels forwards
	// 		this->forwards(this->m_motors[i]);
	// 		// Move the left wheels back
	// 		this->backwards(this->m_motors[4 - 1 - i]);
	// 	}
	// 	// Making the robot move left
	// 	// Return from function
	// 	return;

	// // If stop
	// case Direction::Stop:
	// 	// Itterate through all the motors
	// 	for (pin& motor : this->m_motors)
	// 		// Stop all the motors
	// 		this->stop(motor);
	// 	// Return from function
	// 	return;
	// }
}
