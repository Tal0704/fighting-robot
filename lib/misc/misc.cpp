#include "misc.h"

Servo horizontal, vertical;

unsigned int getDistance()
{
	long duration;

	// start of waking call for the sensor
	digitalWrite(TRIG, LOW);
	delayMicroseconds(2);

	// end of waking call for the sensor
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);

	// sending a signal and seeing the
	// duration that it takes to get back
	digitalWrite(TRIG, LOW);
	duration = pulseIn(ECHO, HIGH);

	// returning the distance in cm
	return duration / 29 / 2;
}

// Activating the buzzer
void buzz(unsigned int delay_ms)
{
	// Output '0' to BUZZER_PIN pin (make sound)
	digitalWrite(BUZZER_PIN, LOW);
	delay(delay_ms);
	// Output '1' to BUZZER_PIN pin (stop makeing sound)
	digitalWrite(BUZZER_PIN, HIGH);
	delay(delay_ms);
	// Output '0' to BUZZER_PIN pin (make sound)
	digitalWrite(BUZZER_PIN, LOW);
	delay(delay_ms);
	// Output '1' to BUZZER_PIN pin (stop makeing sound)
	digitalWrite(BUZZER_PIN, HIGH);
	delay(delay_ms);
}

static std::unordered_map<std::string, Wheel> wheels = {
	{"lb", Wheel(LEFT_BOTTOM_WHEEL_FOR, LEFT_BOTTOM_WHEEL_BACK, MOTOR_EN)},
	{"lt", Wheel(LEFT_TOP_WHEEL_FOR, LEFT_TOP_WHEEL_BACK, MOTOR_EN)},
	{"rb", Wheel(RIGHT_BOTTOM_WHEEL_FOR, RIGHT_BOTTOM_WHEEL_BACK, MOTOR_EN)},
	{"rt", Wheel(RIGHT_TOP_WHEEL_FOR, RIGHT_TOP_WHEEL_BACK, MOTOR_EN)}
};
 
inline void moveWheels()
{
	using namespace firebase::input;

	wheels["lb"] = Wheel(LEFT_BOTTOM_WHEEL_FOR, LEFT_BOTTOM_WHEEL_BACK, MOTOR_EN);
	wheels["lt"] = Wheel(LEFT_TOP_WHEEL_FOR, LEFT_TOP_WHEEL_BACK, MOTOR_EN);
	wheels["rb"] = Wheel(RIGHT_BOTTOM_WHEEL_FOR, RIGHT_BOTTOM_WHEEL_BACK, MOTOR_EN);
	wheels["rt"] = Wheel(RIGHT_TOP_WHEEL_FOR, RIGHT_TOP_WHEEL_BACK, MOTOR_EN);

	wheels["lb"].setPWM(leftStick.strength);
	horizontal.detach();
	horizontal.detach();

	// is the user pushing the stick
	// Forwards
	if(leftStick.angle > 45 && leftStick.angle < 135)
	{
		for(const auto& pair : wheels)
		{
			pair.second.forwards();
		}		

		Serial.println("Forwards");
	}
	// Left
	else if(leftStick.angle > 135 && leftStick.angle < 225)
	{
		wheels["rb"].forwards();
		wheels["rt"].forwards();
		wheels["lb"].backwards();
		wheels["lt"].backwards();
	}
	// Back
	else if(leftStick.angle > 225 && leftStick.angle < 315)
	{
		for(const auto& pair : wheels)
		{
			pair.second.backwards();
		}		
	}
	// Right
	else if(leftStick.angle > 315 || leftStick.angle < 45)
	{
		wheels["rb"].backwards();
		wheels["rt"].backwards();
		wheels["lb"].forwards();
		wheels["lt"].forwards();
	}
}

void doGetFb(StreamData data)
{
	// using the namespace so that we don't have to call it every time
	using namespace firebase::input;
	 
	// using two vectors, one for each joystick
	static Vector ltemp, rtemp;
	 
	// if the path of the data is the strength of the left stick
	if(data.dataPath() == "/controller/leftStick/strength")
	{ 
		// update the strength of the left stick
		leftStick.strength = data.intData();

		//moving the wheels of the robot
		moveWheels();
	}
	// if the path of the data is the angle of the left stick
	if(data.dataPath() == "/controller/leftStick/angle")
	{ 
		// update the angle of the left stick
		leftStick.angle = data.intData();

		//moving the wheels of the robot
		moveWheels();
	}
		 
	// if the path of the data is the x position of the right stick
	if(data.dataPath() == "/controller/rightStick/x")
	{ 
		// writing to the horizontal servo the position it should be at
		horizontal.attach(SERVO_HOR, 500, 2400);
		for(const auto& pair : wheels)
			pair.second.stop();
		horizontal.setPeriodHertz(50);
		horizontal.write(180 - data.intData());
		// Serial.printf("Servo at pos %d, %d\n", horizontal.read(), vertical.read());
	}
	// if the path of the data is the y position of the right stick
	if(data.dataPath() == "/controller/rightStick/y")
	{ 
		// writing to the vertical servo the position it should be at
		vertical.attach(SERVO_VER, 500, 2400);
		for(const auto& pair : wheels)
			pair.second.stop();
		vertical.setPeriodHertz(50);
		vertical.write(180 - data.intData());
		// Serial.printf("Servo at pos %d, %d\n", horizontal.read(), vertical.read());
	}

	// if the path of the data is the laser emitter
	if(data.dataPath() == "/laserEmitter")
	{ 
		// getting if the robot should fire or not 
		if(data.boolData())
		{
			// shooting the laser
			laser::emit();
		}
		else
			// stop shooting the laser
			laser::stopEmitting();
	}
}

void initServo()
{
	Serial.println("Initializing servo");
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	horizontal.setPeriodHertz(50);
	horizontal.attach(SERVO_HOR, 500, 2400);
	horizontal.write(90);

	vertical.setPeriodHertz(50000);
	vertical.attach(SERVO_VER, 500, 2400);
	vertical.write(90);

	Serial.print("Finished initializing servo!\n");
}