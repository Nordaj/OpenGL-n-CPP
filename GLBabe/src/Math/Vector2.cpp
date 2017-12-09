#include "Vector2.h"

Vector2::Vector2()
{ }

Vector2::Vector2(float X, float Y)
	:x(X), y(Y)
{ }

Vector2 Vector2::Add(const Vector2 &other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator+(const Vector2 &other)
{
	return this->Add(other);
}

Vector2 Vector2::operator+=(const Vector2 &other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2 Vector2::Subtract(const Vector2 &other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator-(const Vector2 &other)
{
	return this->Subtract(other);
}

Vector2 Vector2::operator-=(const Vector2 &other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::Multiply(const Vector2 &other)
{
	return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator*(const Vector2 &other)
{
	return this->Multiply(other);
}

Vector2 Vector2::operator*=(const Vector2 &other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

Vector2 Vector2::Divide(const Vector2 &other)
{
	return Vector2(x / other.x, y / other.y);

}

Vector2 Vector2::operator/(const Vector2 &other)
{
	return this->Divide(other);
}

Vector2 Vector2::operator/=(const Vector2 &other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

bool Vector2::operator==(const Vector2 &other)
{
	return (this->x == other.x && this->y == other.y);
}

bool Vector2::operator!=(const Vector2 &other)
{
	return !(this->x == other.x && this->y == other.y);
}

std::ostream &operator<<(std::ostream &stream, const Vector2 &vec)
{
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}
