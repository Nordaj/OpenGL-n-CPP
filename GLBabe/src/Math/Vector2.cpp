#include "Vector2.h"

Vector2::Vector2()
{ }

Vector2::Vector2(float X, float Y)
	:x(X), y(Y)
{ }

float Vector2::Dot(const Vector2 &other)
{
	return (x * other.x) + (y * other.y);
}

float Vector2::Magnitude()
{
	return sqrt((x * x) + (y * y));
}

float Vector2::QMag()
{
	return (x * x) + (y * y);
}

void Vector2::Normalize()
{
	*this /= this->Magnitude();
}

float Vector2::Distance(const Vector2 &other)
{
	Vector2 dif = *this - other;
	return dif.Magnitude();
}

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

Vector2 Vector2::Add(const float &value)
{
	return Vector2(x + value, y + value);
}

Vector2 Vector2::operator+(const float &value)
{
	return this->Add(value);
}

Vector2 Vector2::operator+=(const float &value)
{
	x += value;
	y += value;
	return *this;
}

Vector2 Vector2::Subtract(const float &value)
{
	return Vector2(x - value, y - value);
}

Vector2 Vector2::operator-(const float &value)
{
	return this->Subtract(value);
}

Vector2 Vector2::operator-=(const float &value)
{
	x -= value;
	y -= value;
	return *this;
}

Vector2 Vector2::Multiply(const float &value)
{
	return Vector2(x * value, y * value);
}

Vector2 Vector2::operator*(const float &value)
{
	return this->Multiply(value);
}

Vector2 Vector2::operator*=(const float &value)
{
	x *= value;
	y *= value;
	return *this;
}

Vector2 Vector2::Divide(const float &value)
{
	return Vector2(x * value, y * value);
}

Vector2 Vector2::operator/(const float &value)
{
	return this->Divide(value);
}

Vector2 Vector2::operator/=(const float &value)
{
	x /= value;
	y /= value;
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

float Vector2::Dot(const Vector2 &first, const Vector2 &second)
{
	return (first.x * second.x) + (first.y * second.y);
}

float Vector2::Distance(const Vector2 &first, const Vector2 &second)
{
	Vector2 vec = Vector2(first.x - second.x, first.y - second.y);
	return vec.Magnitude();
}

std::ostream &operator<<(std::ostream &stream, const Vector2 &vec)
{
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}
