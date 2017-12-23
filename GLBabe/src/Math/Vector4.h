#pragma once

#include <iostream>

class Vector4
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
			float r, g, b, a;
		};
	};

private:

public:
	Vector4();
	Vector4(float X, float Y, float Z, float W);

	float Dot(const Vector4 &other);
	float Magnitude();
	float QMag();
	void Normalize();
	float Distance(const Vector4 &other);

	Vector4 Add(const Vector4 &other);
	Vector4 operator+(const Vector4 &other);
	Vector4 operator+=(const Vector4 &other);

	Vector4 Subtract(const Vector4 &other);
	Vector4 operator-(const Vector4 &other);
	Vector4 operator-=(const Vector4 &other);

	Vector4 Multiply(const Vector4 &other);
	Vector4 operator*(const Vector4 &other);
	Vector4 operator*=(const Vector4 &other);

	Vector4 Divide(const Vector4 &other);
	Vector4 operator/(const Vector4 &other);
	Vector4 operator/=(const Vector4 &other);

	Vector4 Add(float value);
	Vector4 operator+(float value);
	Vector4 operator+=(float value);

	Vector4 Subtract(float value);
	Vector4 operator-(float value);
	Vector4 operator-=(float value);

	Vector4 Multiply(float value);
	Vector4 operator*(float value);
	Vector4 operator*=(float value);

	Vector4 Divide(float value);
	Vector4 operator/(float value);
	Vector4 operator/=(float value);

	bool operator==(const Vector4 &other);
	bool operator!=(const Vector4 &other);

	static float Dot(const Vector4 &first, const Vector4 &second);
	static float Distance(const Vector4 &first, const Vector4 &second);

	friend std::ostream &operator<<(std::ostream &stream, Vector4 &vec);
};
