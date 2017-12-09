#pragma once

#include <iostream>
#include <glm/vec2.hpp>

class Vector2
{
public:
	float x, y;

private:

public:
	Vector2();
	Vector2(float X, float Y);

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

	bool operator==(const Vector2 &other);
	bool operator!=(const Vector2 &other);

	friend std::ostream &operator<<(std::ostream &stream, const Vector2 &vec);
};
