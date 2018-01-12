#pragma once

#include <iostream>

#include "Vector3.h"

class Quaternion 
{
public:
	union
	{
		struct 
		{
			float x, y, z, w;
		};

		struct
		{
			float i, j, k, r;
		};

		struct
		{
			Vector3 v;
			float s;
		};
	};
	//float x, y, z, w;

private:

public:
	Quaternion();
	Quaternion(Vector3 &axis, float angle);
	Quaternion(float X, float Y, float Z, float W);

	float Magnitude();
	Quaternion Normalize();

	Quaternion Rotate(Vector3 &axis, float rot);
	Quaternion Rotate(Vector3 &rot);

	Quaternion Multiply(Quaternion &other);
	Quaternion operator*(Quaternion &other);
	Quaternion operator*=(Quaternion &other);

	static Quaternion FromEuler(Vector3 &euler);

	friend std::ostream &operator<<(std::ostream &stream, Quaternion &quat);
};
