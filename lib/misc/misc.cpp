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
 
void doGetFb(StreamData data)
{
	using namespace firebase::input;
	static Vector ltemp, rtemp;
	if(data.dataPath() == "/controller/leftStick/strength")
	{ 
		// getting the strength of the left stick
		ltemp.strength = data.intData();
		leftStick = convertPolarToCartezian(ltemp);
	}
	if(data.dataPath() == "/controller/leftStick/angle")
	{ 
		// getting the angle of the left stick
		ltemp.angle = data.intData();
		leftStick = convertPolarToCartezian(ltemp);
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
		// getting if the robot should fire or not 
		firebase::input::isShooting = data.boolData(); 

#if defined(_DEBUG)
		Serial.printf("\nleft stick: str: %d, ang: %d\n", leftStick.strength, leftStick.angle);
		Serial.printf("\nright stick: str: %d, ang: %d\n", rightStick.strength, rightStick.angle);
		Serial.printf("%s", isShooting ? "true\n": "false\n");
#endif
}
 
void initMotors()
{
	digitalWrite(LEFT_TOP_WHEEL, OUTPUT);
	digitalWrite(RIGHT_TOP_WHEEL, OUTPUT);
	digitalWrite(LEFT_BOTTOM_WHEEL, OUTPUT);
	digitalWrite(RIGHT_BOTTOM_WHEEL, OUTPUT);
	Serial.println("Initialized motors");
}