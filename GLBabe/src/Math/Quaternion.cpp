#include <vector>

#include "Vector3.h"
#include "Misc.h"

#include "Quaternion.h"

Quaternion::Quaternion()
	:x(0), y(0), z(0), w(1)
{ }

Quaternion::Quaternion(Vector3 vec, float W)
	: x(vec.x), y(vec.y), z(vec.z), w(W)
{ }

Quaternion::Quaternion(float X, float Y, float Z, float W)
	:x(X), y(Y), z(Z), w(W)
{ }

float Quaternion::Magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

Quaternion Quaternion::Normalize()
{
	float mag = this->Magnitude();

	x /= mag;
	y /= mag;
	z /= mag;
	w /= mag;

	return *this;
}

Quaternion Quaternion::Rotate(float rot, Vector3 &axis)
{
	Quaternion quat;

	rot = Radians(rot);

	quat.x = axis.x * sinf(rot / 2);
	quat.y = axis.y * sinf(rot / 2);
	quat.z = axis.z * sinf(rot / 2);
	quat.w = cosf(rot / 2);

	*this = quat * *this;

	return *this;
}

Quaternion Quaternion::Rotate(Vector3 &rot)
{
	Quaternion quat;

	float cosX = cos(Radians(rot.x) * 0.5f);
	float cosY = cos(Radians(rot.y) * 0.5f);
	float cosZ = cos(Radians(rot.z) * 0.5f);
	float sinX = sin(Radians(rot.x) * 0.5f);
	float sinY = sin(Radians(rot.y) * 0.5f);
	float sinZ = sin(Radians(rot.z) * 0.5f);

	quat.x = (cosZ * cosY * sinX) - (sinZ * sinY * cosX);
	quat.y = (cosZ * sinY * cosX) + (sinZ * cosY * sinX);
	quat.z = (sinZ * cosY * cosX) - (cosZ * sinY * sinX);
	quat.w = (cosZ * cosY * cosX) + (sinZ * sinY * sinX);

	*this = quat * *this;

	return *this;
}

Quaternion Quaternion::Multiply(Quaternion &other)
{
	Quaternion quat;

	//(Q1 * Q2).x = (w1x2 + x1w2 + y1z2 - z1y2)
	quat.x = (w * other.x) + (x * other.w) + (y * other.z) - (z * other.y);

	//(Q1 * Q2).y = (w1y2 - x1z2 + y1w2 + z1x2)
	quat.y = (w * other.y) - (x * other.z) + (y * other.w) + (z * other.x);

	//(Q1 * Q2).z = (w1z2 + x1y2 - y1x2 + z1w2)
	quat.z = (w * other.z) + (x * other.y) - (y * other.x) + (z * other.w);
	
	//(Q1 * Q2).w = (w1w2 - x1x2 - y1y2 - z1z2)
	quat.w = (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z);

	return quat;
}

Quaternion Quaternion::operator*(Quaternion &other)
{
	return this->Multiply(other);
}

Quaternion Quaternion::operator*=(Quaternion &other)
{
	Quaternion quat;

	//(Q1 * Q2).x = (w1x2 + x1w2 + y1z2 - z1y2)
	x = (w * quat.x) + (x * other.w) + (y * other.z) - (z * other.y);

	//(Q1 * Q2).y = (w1y2 - x1z2 + y1w2 + z1x2)
	y = (w * other.y) - (x * other.z) + (y * other.w) + (z * other.x);

	//(Q1 * Q2).z = (w1z2 + x1y2 - y1x2 + z1w2)
	z = (w * other.z) + (x * other.y) - (y * other.x) + (z * other.w);

	//(Q1 * Q2).w = (w1w2 - x1x2 - y1y2 - z1z2)
	w = (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z);

	return *this;
}

std::ostream &operator<<(std::ostream &stream, Quaternion &quat)
{
	stream << "(" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ")";
	return stream;
}