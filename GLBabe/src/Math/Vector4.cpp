#include "Vector4.h"

Vector4::Vector4()
{
}

Vector4::Vector4(float X, float Y, float Z, float W)
	:x(X), y(Y), z(Z), w(W)
{
}

float Vector4::Dot(const Vector4 &other)
{
	return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

float Vector4::Magnitude()
{
	return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

float Vector4::QMag()
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

void Vector4::Normalize()
{
	*this /= this->Magnitude();
}

float Vector4::Distance(const Vector4 &other)
{
	Vector4 dif = *this - other;
	return dif.Magnitude();
}

Vector4 Vector4::Add(const Vector4 &other)
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator+(const Vector4 &other)
{
	return this->Add(other);
}

Vector4 Vector4::operator+=(const Vector4 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

Vector4 Vector4::Subtract(const Vector4 &other)
{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::operator-(const Vector4 &other)
{
	return this->Subtract(other);
}

Vector4 Vector4::operator-=(const Vector4 &other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vector4 Vector4::Multiply(const Vector4 &other)
{
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

Vector4 Vector4::operator*(const Vector4 &other)
{
	return this->Multiply(other);
}

Vector4 Vector4::operator*=(const Vector4 &other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
	return *this;
}

Vector4 Vector4::Divide(const Vector4 &other)
{
	return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}

Vector4 Vector4::operator/(const Vector4 &other)
{
	return this->Divide(other);
}

Vector4 Vector4::operator/=(const Vector4 &other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
	return *this;
}

Vector4 Vector4::Add(float value)
{
	return Vector4(x + value, y + value, z + value, w + value);
}

Vector4 Vector4::operator+(float value)
{
	return this->Add(value);
}

Vector4 Vector4::operator+=(float value)
{
	x += value;
	y += value;
	z += value;
	w += value;
	return *this;
}

Vector4 Vector4::Subtract(float value)
{
	return Vector4(x - value, y - value, z - value, w - value);
}

Vector4 Vector4::operator-(float value)
{
	return this->Subtract(value);
}

Vector4 Vector4::operator-=(float value)
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;
	return *this;
}

Vector4 Vector4::Multiply(float value)
{
	return Vector4(x * value, y * value, z * value, w * value);
}

Vector4 Vector4::operator*(float value)
{
	return this->Multiply(value);
}

Vector4 Vector4::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
	return *this;
}

Vector4 Vector4::Divide(float value)
{
	return Vector4(x / value, y / value, z / value, w / value);
}

Vector4 Vector4::operator/(float value)
{
	return this->Divide(value);
}

Vector4 Vector4::operator/=(float value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
	return *this;
}

bool Vector4::operator==(const Vector4 &other)
{
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}

bool Vector4::operator!=(const Vector4 &other)
{
	return !(x == other.x && y == other.y && z == other.z && w == other.w);
}

float Vector4::Dot(const Vector4 &first, const Vector4 &second)
{
	return (first.x * second.x) + (first.y * second.y) + (first.z * second.z) + (first.w * second.w);
}

float Vector4::Distance(const Vector4 &first, const Vector4 &second)
{
	//Cant do first - second, gotta do it like this
	Vector4 dif = Vector4(first.x - second.x, first.y - second.y, first.z - second.z, first.w - second.w);
	return dif.Magnitude();
}

std::ostream &operator<<(std::ostream &stream, Vector4 &vec)
{
	stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	return stream;
}
