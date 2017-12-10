#pragma once

#include <iostream>

class Vector3
{
public:
	float x, y, z;

private:

public:
	Vector3();
	Vector3(float X, float Y, float Z);

	Vector3 Add(const Vector3 &other);
	Vector3 operator+(const Vector3 &other);
	Vector3 operator+=(const Vector3 &other);

	Vector3 Subtract(const Vector3 &other);
	Vector3 operator-(const Vector3 &other);
	Vector3 operator-=(const Vector3 &other);

	Vector3 Multiply(const Vector3 &other);
	Vector3 operator*(const Vector3 &other);
	Vector3 operator*=(const Vector3 &other);

	Vector3 Divide(const Vector3 &other);
	Vector3 operator/(const Vector3 &other);
	Vector3 operator/=(const Vector3 &other);

	bool operator==(const Vector3 &other);
	bool operator!=(const Vector3 &other);

	friend std::ostream &operator<<(std::ostream &stream, Vector3 &vec);
};
