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
	 
	digitalWrite(LEFT_TOP_WHEEL, HIGH);
	digitalWrite(RIGHT_TOP_WHEEL, HIGH);
	digitalWrite(LEFT_BOTTOM_WHEEL, HIGH);
	digitalWrite(RIGHT_BOTTOM_WHEEL, HIGH);
	 
	Serial.println("Initialized motors");
}

void doGetFb(StreamData data)
{
	using namespace firebase::input;
	static Vector ltemp, rtemp;
	if(data.dataPath() == "/controller/leftStick/strength")
	{ 
		// getting the strength of the left stick
		leftStick.strength = data.intData();
		Serial.printf("x: %lf, y: %lf\n", leftStick.x, leftStick.y);
		moveWheels();
	}
	if(data.dataPath() == "/controller/leftStick/angle")
	{ 
		// getting the angle of the left stick
		leftStick.angle = data.intData();
		Serial.printf("x: %lf, y: %lf\n", leftStick.x, leftStick.y);
		moveWheels();
	}
		 
	if(data.dataPath() == "/controller/rightStick/strength")
	{ 
		// getting the strength of the right stick
		rtemp.strength = data.intData();
		rightStick = convertPolarToCartezian(rtemp);
		servo::horizontal.write(rightStick.x);
		// Serial.printf("x: %lf, y: %lf\n", rightStick.x, rightStick.y);
	}
	if(data.dataPath() == "/controller/rightStick/angle")
	{ 
		// getting the angle of the right stick
		rtemp.angle = data.intData();
		rightStick = convertPolarToCartezian(rtemp);
		servo::horizontal.write(rightStick.x);
		// Serial.printf("x: %lf, y: %lf\n", rightStick.x, rightStick.y);
	}

	if(data.dataPath() == "/laserEmitter")
	{ 
		// getting if the robot should fire or not 
		if(data.boolData())
		{ 
			digitalWrite(LASER_EMIT, HIGH);
			Serial.println("asdasd");
		}
		else
			digitalWrite(LASER_EMIT, LOW);
	}

	delay(50);
#if defined(_DEBUG)
		Serial.printf("\nleft stick: str: %d, ang: %d\n", leftStick.strength, leftStick.angle);
		Serial.printf("\nright stick: str: %d, ang: %d\n", rightStick.strength, rightStick.angle);
		Serial.printf("%s", isShooting ? "true\n": "false\n");
#endif
}