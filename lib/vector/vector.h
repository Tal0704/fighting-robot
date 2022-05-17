#pragma once

union Vector
{
	struct
	{
		int angle, strength;
	};

	struct
	{
		int x, y;
	};

	Vector()
		: x(0), y(0) {}

	Vector(int x, int y)
		: x(x), y(y) {}
};
