#include "misc.h"

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
}

Vector convertPolarToCartezian(const Vector &vect)
{
	return Vector(vect.strength * cosf(vect.angle), vect.strength * sinf(vect.angle));
}
 
void moveWheels()
{
	using namespace firebase::input;
	if(leftStick.strength > 0)
	{ 
		if(leftStick.angle > 45 && leftStick.angle < 135)
		{
			digitalWrite(LEFT_TOP_WHEEL, HIGH);
			digitalWrite(RIGHT_TOP_WHEEL, HIGH);
			digitalWrite(LEFT_BOTTOM_WHEEL, LOW);
			digitalWrite(RIGHT_BOTTOM_WHEEL, LOW);
			Serial.println("Top");
		}
		else if(leftStick.angle > 135 && leftStick.angle < 225)
		{
			digitalWrite(LEFT_TOP_WHEEL, LOW);
			digitalWrite(RIGHT_TOP_WHEEL, HIGH);
			digitalWrite(LEFT_BOTTOM_WHEEL, LOW);
			digitalWrite(RIGHT_BOTTOM_WHEEL, HIGH);
			Serial.println("Left");
		}
		else if(leftStick.angle > 225 && leftStick.angle < 315)
		{
			digitalWrite(LEFT_TOP_WHEEL, LOW);
			digitalWrite(RIGHT_TOP_WHEEL, LOW);
			digitalWrite(LEFT_BOTTOM_WHEEL, HIGH);
			digitalWrite(RIGHT_BOTTOM_WHEEL, HIGH);
			Serial.println("Bottom");
		}
		else if(leftStick.angle > 315 || leftStick.angle < 45)
		{
			digitalWrite(LEFT_TOP_WHEEL, HIGH);
			digitalWrite(RIGHT_TOP_WHEEL, LOW);
			digitalWrite(LEFT_BOTTOM_WHEEL, HIGH);
			digitalWrite(RIGHT_BOTTOM_WHEEL, LOW);
			Serial.println("Right");
		}
	}
	else
	{
		digitalWrite(LEFT_TOP_WHEEL, LOW);
		digitalWrite(RIGHT_TOP_WHEEL, LOW);
		digitalWrite(LEFT_BOTTOM_WHEEL, LOW);
		digitalWrite(RIGHT_BOTTOM_WHEEL, LOW);
		Serial.println("Stop");
	}
}
 
void initMotors()
{
	pinMode(LEFT_TOP_WHEEL, OUTPUT);
	pinMode(RIGHT_TOP_WHEEL, OUTPUT);
	pinMode(LEFT_BOTTOM_WHEEL, OUTPUT);
	pinMode(RIGHT_BOTTOM_WHEEL, OUTPUT);
	 
	digitalWrite(LEFT_TOP_WHEEL, LOW);
	digitalWrite(RIGHT_TOP_WHEEL, LOW);
	digitalWrite(LEFT_BOTTOM_WHEEL, LOW);
	digitalWrite(RIGHT_BOTTOM_WHEEL, LOW);
	 
	Serial.println("Initialized motors");
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
		// getting the strength of the left stick
		leftStick.strength = data.intData();
		// moveing the wheels
		moveWheels();
	}
	// if the path of the data is the angle of the left stick
	if(data.dataPath() == "/controller/leftStick/angle")
	{ 
		// getting the angle of the left stick
		leftStick.angle = data.intData();
		// moveing the wheels
		moveWheels();
	}
		 
	// if the path of the data is the strength of the left stick
	if(data.dataPath() == "/controller/rightStick/strength")
	{ 
		// getting the strength of the right stick
		rtemp.strength = data.intData();
		// converting the data from polar to Cartezian form
		rightStick = convertPolarToCartezian(rtemp);
		// moving the horizontal servo to the right angle
		servo::horizontal.write(rightStick.x);
		Serial.printf("Servo is in pos: %d\n", servo::horizontal.read());
	}
	// if the path of the data is the angle of the right stick
	if(data.dataPath() == "/controller/rightStick/angle")
	{ 
		// getting the angle of the right stick
		rtemp.angle = data.intData();
		// converting the data from polar to Cartezian form
		rightStick = convertPolarToCartezian(rtemp);
		// moving the horizontal servo to the right angle
		servo::horizontal.write(rightStick.x);
		Serial.printf("Servo is in pos: %d\n", servo::horizontal.read());
	}

	// if the path of the data is the laser emitter
	if(data.dataPath() == "/laserEmitter")
	{ 
		// getting if the robot should fire or not 
		if(data.boolData())
			// shooting the laser
			laser::emit();
		else
			// stop shooting the laser
			laser::stopEmitting();
	}

	// setting up a slight delay to avoid problems with the cores
	delay(50);
}