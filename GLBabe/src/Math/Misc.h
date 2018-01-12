#pragma once

#define _USE_MATH_DEFINES
#define F_PI 3.141f

#include <math.h>

static float Radians(float degrees)
{
	//return degrees * (F_PI / 180);
	//return (degrees * F_PI) / 180;
	return degrees * 0.0174532925;
}

static float Degrees(float radians)
{
	//return radians * (180 / F_PI);
	//return (radians * 180) / F_PI;
	return radians * 57.2957795;
}
