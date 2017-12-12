#pragma once

#include <iostream>

class Vector2
{
public:
	float x, y;

private:

public:
	Vector2();
	Vector2(float X, float Y);

	float Dot(const Vector2 &other);
	float Magnitude();
	float QMag();
	void Normalize();
	float Distance(const Vector2 &other);

	Vector2 Add(const Vector2 &other);
	Vector2 operator+(const Vector2 &other);
	Vector2 operator+=(const Vector2 &other);

	Vector2 Subtract(const Vector2 &other);
	Vector2 operator-(const Vector2 &other);
	Vector2 operator-=(const Vector2 &other);

	Vector2 Multiply(const Vector2 &other);
	Vector2 operator*(const Vector2 &other);
	Vector2 operator*=(const Vector2 &other);

	Vector2 Divide(const Vector2 &other);
	Vector2 operator/(const Vector2 &other);
	Vector2 operator/=(const Vector2 &other);

	Vector2 Add(const float &value);
	Vector2 operator+(const float &value);
	Vector2 operator+=(const float &value);

	Vector2 Subtract(const float &value);
	Vector2 operator-(const float &value);
	Vector2 operator-=(const float &value);

	Vector2 Multiply(const float &value);
	Vector2 operator*(const float &value);
	Vector2 operator*=(const float &value);

	Vector2 Divide(const float &value);
	Vector2 operator/(const float &value);
	Vector2 operator/=(const float &value);

	bool operator==(const Vector2 &other);
	bool operator!=(const Vector2 &other);

	static float Dot(const Vector2 &first, const Vector2 &second);
	static float Distance(const Vector2 &first, const Vector2 &second);

	friend std::ostream &operator<<(std::ostream &stream, const Vector2 &vec);
};
