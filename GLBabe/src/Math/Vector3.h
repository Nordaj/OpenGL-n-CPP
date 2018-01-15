#pragma once

#include <iostream>

class Vector3
{
public:
	union 
	{
		struct 
		{
			float x, y, z;
		};

		struct 
		{
			float r, g, b;
		};
	};

private:

public:
	Vector3();
	Vector3(float X, float Y, float Z);

	float Dot(const Vector3 &other);
	float Magnitude() const;
	float QMag();
	void Normalize();
	Vector3 Normalized() const;
	Vector3 Cross(const Vector3 &other);
	float Distance(const Vector3 &other);

	Vector3 Add(const Vector3 &other) const;
	Vector3 operator+(const Vector3 &other) const;
	Vector3 operator+=(const Vector3 &other);

	Vector3 Subtract(const Vector3 &other) const;
	Vector3 operator-(const Vector3 &other) const;
	Vector3 operator-=(const Vector3 &other);

	Vector3 Multiply(const Vector3 &other) const;
	Vector3 operator*(const Vector3 &other) const;
	Vector3 operator*=(const Vector3 &other);

	Vector3 Divide(const Vector3 &other) const;
	Vector3 operator/(const Vector3 &other) const;
	Vector3 operator/=(const Vector3 &other);

	Vector3 Add(float value) const;
	Vector3 operator+(float value) const;
	Vector3 operator+=(float value);

	Vector3 Subtract(float value) const;
	Vector3 operator-(float value) const;
	Vector3 operator-=(float value);

	Vector3 Multiply(float value) const;
	Vector3 operator*(float value) const;
	Vector3 operator*=(float value);

	Vector3 Divide(float value) const;
	Vector3 operator/(float value) const;
	Vector3 operator/=(float value);

	bool operator==(const Vector3 &other);
	bool operator!=(const Vector3 &other);

	static float Dot(const Vector3 &first, const Vector3 &second);
	static Vector3 Cross(const Vector3 &first, const Vector3 &second);
	static float Distance(const Vector3 &first, const Vector3 &second);

	friend std::ostream &operator<<(std::ostream &stream, Vector3 &vec);
};
