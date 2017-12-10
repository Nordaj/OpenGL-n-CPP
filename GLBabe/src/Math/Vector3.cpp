#include "Vector3.h"

Vector3::Vector3()
{ }

Vector3::Vector3(float X, float Y, float Z)
	:x(X), y(Y), z(Z)
{ }

Vector3 Vector3::Add(const Vector3 &other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+(const Vector3 &other)
{
	return this->Add(other);
}

Vector3 Vector3::operator+=(const Vector3 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3 Vector3::Subtract(const Vector3 &other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-(const Vector3 &other)
{
	return this->Subtract(other);
}

Vector3 Vector3::operator-=(const Vector3 &other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3 Vector3::Multiply(const Vector3 &other)
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(const Vector3 &other)
{
	return this->Multiply(other);
}

Vector3 Vector3::operator*=(const Vector3 &other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vector3 Vector3::Divide(const Vector3 &other)
{
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator/(const Vector3 &other)
{
	return this->Divide(other);
}

Vector3 Vector3::operator/=(const Vector3 &other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

bool Vector3::operator==(const Vector3 &other)
{
	return (x == other.x, y == other.y, z == other.z);
}

bool Vector3::operator!=(const Vector3 &other)
{
	return !(x == other.x, y == other.y, z == other.z);
}

std::ostream &operator<<(std::ostream &stream, Vector3 &vec)
{
	stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return stream;
}
