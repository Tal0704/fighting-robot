#pragma once

union Vector
{
	struct
	{
		float angle, strength;
	};

	struct 
	{
		float x, y;
	};

	Vector()
		: x(0), y(0) {}

	Vector(float x, float y)
		: x(x), y(y) {}
};