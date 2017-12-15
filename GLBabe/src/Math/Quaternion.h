#pragma once

#include <iostream>

#include "Vector3.h"

class Quaternion 
{
public:
	float x, y, z, w;

private:

public:
	Quaternion();
	Quaternion(Vector3 vec, float W);
	Quaternion(float X, float Y, float Z, float W);

	float Magnitude();
	Quaternion Normalize();

	Quaternion Rotate(float rot, Vector3 &axis);
	Quaternion Rotate(Vector3 &rot);

	Quaternion Multiply(Quaternion &other);
	Quaternion operator*(Quaternion &other);
	Quaternion operator*=(Quaternion &other);

	friend std::ostream &operator<<(std::ostream &stream, Quaternion &quat);
};
