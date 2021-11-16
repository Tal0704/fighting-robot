#include "input.h"

void Input::moveWheels(Wheels &wheels)
{
	wheels.enable();

	if (fabs(this->lStick.x) <= 15.0f && fabs(this->lStick.y) <= 15.0f) // Checking if the joystick is in the dead zone
	{
		wheels.move(Wheels::Directions::Stop);
		wheels.disable();
		return;
	}

	if (this->lStick.x != 0) // Stopping div by zero
		// Using sin to get the angle of the stick
		this->input.angle = sin(this->lStick.y / this->lStick.x);
	else
		this->input.angle = 0.0f;

	// Using the pythagorean theorem to solve for the strength that was pushed
	this->input.strength = sqrt(fabs(this->lStick.y * this->lStick.y) + fabs(this->lStick.x * this->lStick.x));

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
	lStick.x = (analogRead(L_STICK_X) - 1970);
	lStick.y = (analogRead(L_STICK_Y) - 1920);
	lStick.z = (digitalRead(L_STICK_Z));
}

void *reciveFunc(void *param)
{
	Vector input;
	
	FirebaseData fbdata;
	if (Firebase.getInt(fbdata, "/processor/controller/leftStick/strength"))
		input.strength = fbdata.intData();
	if (Firebase.getInt(fbdata, "/processor/controller/leftStick/angle"))
	{
		input.angle = fbdata.intData() - 90;
		if (input.angle < 0)
			input.angle += 360;
		Serial.printf("Strength: %.0lf, angle: %.0lf", input.strength, input.angle);
	}
}

void Input::getInputApp()
{
	Vector input;

	FirebaseData fbdata;
	if (Firebase.getInt(fbdata, "/processor/controller/leftStick/strength"))
		input.strength = fbdata.intData();
	if (Firebase.getInt(fbdata, "/processor/controller/leftStick/angle"))
	{
		input.angle = fbdata.intData();
		Serial.printf("Strength: %.0lf, angle: %.0lf\n", input.strength, input.angle);
	}
}

static Vector controllerData;

void OnDataRecive(const uint8_t *mac, const uint8_t *incomingData, int len)
{
	memcpy(&controllerData, incomingData, sizeof(controllerData));
}

void Input::getInputController()
{
	const char controller[] = WROVER_E_MAC;
	
	esp_now_peer_info_t peerInfo;


	memcpy(peerInfo.peer_addr, controller, 6); // 6 is the size of the mac address in bytes
	peerInfo.channel = 0;
	peerInfo.encrypt = false;

	if (esp_now_add_peer(&peerInfo) != ESP_OK)
	{
		#if defined(_DEBUG)
		Serial.println("Failed to add peer");
		#endif

		return;
	}

	while(1)
	{
		esp_now_register_recv_cb(OnDataRecive);
	}
}
