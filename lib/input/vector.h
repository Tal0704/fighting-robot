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
};