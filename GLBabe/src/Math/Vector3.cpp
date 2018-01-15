#include "Vector3.h"

Vector3::Vector3()
{ }

Vector3::Vector3(float X, float Y, float Z)
	:x(X), y(Y), z(Z)
{ }

float Vector3::Dot(const Vector3 &other)
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

float Vector3::Magnitude() const
{
	return sqrt((x * x) + (y * y) + (z * z));
}

float Vector3::QMag()
{
	return (x * x) + (y * y) + (z * z);
}

void Vector3::Normalize()
{
	*this /= this->Magnitude();
}

Vector3 Vector3::Normalized() const
{ 
	return *this / this->Magnitude();
}

Vector3 Vector3::Cross(const Vector3 &other)
{
	Vector3 vect = Vector3();

	vect.x = y * other.z - z * other.y;
	vect.y = z * other.x - x * other.z;
	vect.z = x * other.y - y * other.x;

	return vect;
}

float Vector3::Distance(const Vector3 &other)
{
	Vector3 dif = *this - other;
	return dif.Magnitude();
}

Vector3 Vector3::Add(const Vector3 &other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+(const Vector3 &other) const
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

Vector3 Vector3::Subtract(const Vector3 &other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const
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

Vector3 Vector3::Multiply(const Vector3 &other) const
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(const Vector3 &other) const
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

Vector3 Vector3::Divide(const Vector3 &other) const
{
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator/(const Vector3 &other) const
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

Vector3 Vector3::Add(float value) const
{
	return Vector3(x + value, y + value, z + value);
}

Vector3 Vector3::operator+(float value) const
{
	return this->Add(value);
}

Vector3 Vector3::operator+=(float value)
{
	x += value;
	y += value;
	z += value;
	return *this;
}

Vector3 Vector3::Subtract(float value) const
{
	return Vector3(x - value, y - value, z - value);
}

Vector3 Vector3::operator-(float value) const
{
	return this->Subtract(value);
}

Vector3 Vector3::operator-=(float value)
{
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

Vector3 Vector3::Multiply(float value) const
{
	return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator*(float value) const
{
	return this->Multiply(value);
}

Vector3 Vector3::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vector3 Vector3::Divide(float value) const
{
	return Vector3(x / value, y / value, z / value);
}

Vector3 Vector3::operator/(float value) const
{
	return this->Divide(value);
}

Vector3 Vector3::operator/=(float value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

bool Vector3::operator==(const Vector3 &other)
{
	return (x == other.x && y == other.y && z == other.z);
}

bool Vector3::operator!=(const Vector3 &other)
{
	return !(x == other.x && y == other.y && z == other.z);
}

float Vector3::Dot(const Vector3 &first, const Vector3 &second)
{
	return (first.x * second.x) + (first.y + second.y) + (first.z + second.z);
}

Vector3 Vector3::Cross(const Vector3 &first, const Vector3 &second)
{
	Vector3 vect = Vector3();

	vect.x = first.y * second.z - first.z * second.y;
	vect.y = first.z * second.x - first.x * second.z;
	vect.z = first.x * second.y - first.y * second.x;

	return vect;
}

float Vector3::Distance(const Vector3 &first, const Vector3 &second)
{
	Vector3 dif = Vector3(first.x - second.x, first.y - second.y, first.z - second.z);
	return dif.Magnitude();
}

std::ostream &operator<<(std::ostream &stream, Vector3 &vec)
{
	stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return stream;
}
