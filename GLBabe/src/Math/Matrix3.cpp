#include <iostream>
#include <math.h>
#include <vector>

#include "Misc.h"
#include "Quaternion.h"

#include "Matrix3.h"

Matrix3::Matrix3()
{
	//Diagonal
	elements[0] = 1;
	elements[4] = 1;
	elements[8] = 1;

	//Everything else
	elements[1] = 0;
	elements[2] = 0;

	elements[3] = 0;
	elements[5] = 0;

	elements[6] = 0;
	elements[7] = 0;
}

Matrix3::Matrix3(float diagonal)
{
	//Diagonal
	elements[0] = diagonal;
	elements[4] = diagonal;
	elements[8] = diagonal;

	//Everything else
	elements[1] = 0;
	elements[2] = 0;

	elements[3] = 0;
	elements[5] = 0;

	elements[6] = 0;
	elements[7] = 0;
}

Matrix3::Matrix3(const std::vector<float> &e)
{
	for (int i = 0; i < 9; i++)
		elements[i] = e[i];
}

Matrix3::Matrix3(const Quaternion &quat)
{
	e[0] = 1 - (2 * (quat.y * quat.y)) - (2 * (quat.z * quat.z));
	e[4] = 1 - (2 * (quat.x * quat.x)) - (2 * (quat.z * quat.z));
	e[8] = 1 - (2 * (quat.x * quat.x)) - (2 * (quat.y * quat.y));

	e[3] = (2 * (quat.x * quat.y)) - (2 * (quat.w * quat.z));
	e[6] = (2 * (quat.x * quat.z)) + (2 * (quat.w * quat.y));

	e[1] = (2 * (quat.x * quat.y)) + (2 * (quat.w * quat.z));
	e[7] = (2 * (quat.y * quat.z)) - (2 * (quat.w * quat.x));

	e[2] = (2 * (quat.x * quat.z)) - (2 * (quat.w * quat.y));
	e[5] = (2 * (quat.y * quat.z)) + (2 * (quat.w * quat.x));
}

float Matrix3::GetDeterminant() const
{
	return (e[0] * e[4] * e[8]) + (e[3] * e[6] * e[2]) + (e[6] * e[1] * e[5]) - 
		   (e[0] * e[7] * e[5]) - (e[3] * e[1] * e[8]) - (e[6] * e[4] * e[2]);
}

Matrix3 Matrix3::Transpose()
{
	Matrix3 OG = *this;

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			elements[x * 3 + y] = OG.elements[y * 3 + x];
		}
	}

	return *this;
}

Matrix3 Matrix3::GetTransposed() const
{
	Matrix3 mat;

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			mat.elements[x * 3 + y] = elements[y * 3 + x];
		}
	}

	return mat;
}

Matrix3 Matrix3::Invert()
{
	float det = GetDeterminant();

	Matrix3 temp = Matrix3();

	temp.m00 = ((m11 * m22) - (m12 * m21));
	temp.m10 = ((m12 * m20) - (m10 * m22));
	temp.m20 = ((m10 * m21) - (m11 * m20));

	temp.m01 = ((m02 * m21) - (m01 * m22));
	temp.m11 = ((m00 * m22) - (m02 * m20));
	temp.m21 = ((m01 * m20) - (m00 * m21));

	temp.m02 = ((m01 * m12) - (m02 * m11));
	temp.m12 = ((m02 * m10) - (m00 * m12));
	temp.m22 = ((m00 * m11) - (m01 * m10));

	temp /= det;
	*this = temp;
	return *this;
}

Matrix3 Matrix3::Inverse() const
{
	float det = GetDeterminant();

	Matrix3 temp = Matrix3();

	temp.m00 = ((m11 * m22) - (m12 * m21));
	temp.m10 = ((m12 * m20) - (m10 * m22));
	temp.m20 = ((m10 * m21) - (m11 * m20));

	temp.m01 = ((m02 * m21) - (m01 * m22));
	temp.m11 = ((m00 * m22) - (m02 * m20));
	temp.m21 = ((m01 * m20) - (m00 * m21));

	temp.m02 = ((m01 * m12) - (m02 * m11));
	temp.m12 = ((m02 * m10) - (m00 * m12));
	temp.m22 = ((m00 * m11) - (m01 * m10));

	temp /= det;
	return temp;
}

Matrix3 Matrix3::Multiply(const Matrix3 &other)
{
	*this = Multiply(*this, other);
	return *this;
}

Matrix3 Matrix3::operator*(const Matrix3 &other) const
{
	return Multiply(*this, other);
}

Matrix3 Matrix3::operator*=(const Matrix3 &other)
{
	Multiply(other);
	return *this;
}

Matrix3 Matrix3::Divide(float other)
{
	*this = Divide(*this, other);
	return *this;
}

Matrix3 Matrix3::operator/(float other) const
{
	return Divide(*this, other);
}

Matrix3 Matrix3::operator/=(float other)
{
	*this = Divide(*this, other);
	return *this;
}

Matrix3 Matrix3::Rotate(const Vector3 &axis, float angle)
{
	Matrix3 mat = Matrix3();

	angle = Radians(angle);

	float c = cos(angle);
	float s = sin(angle);

	mat.e[0] = axis.x * axis.x * ((1 - c) + c);
	mat.e[4] = axis.y * axis.y * ((1 - c) + c);
	mat.e[8] = axis.z * axis.z * ((1 - c) + c);

	mat.e[1] = (axis.x * axis.y) * (1 - c) + (axis.z * s);
	mat.e[2] = (axis.x * axis.z) * (1 - c) - (axis.z * s);

	mat.e[3] = (axis.y * axis.x) * (1 - c) - (axis.z * s);
	mat.e[5] = (axis.y * axis.z) * (1 - c) + (axis.x * s);

	mat.e[6] = (axis.z * axis.x) * (1 - c) + (axis.y * s);
	mat.e[7] = (axis.y * axis.z) * (1 - c) - (axis.x * s);

	*this *= mat;

	return *this;
}

Matrix3 Matrix3::Rotate(const Quaternion &quat)
{
	Matrix3 mat = Matrix3();

	mat.e[0] = 1 - (2 * (quat.y * quat.y)) - (2 * (quat.z * quat.z));
	mat.e[4] = 1 - (2 * (quat.x * quat.x)) - (2 * (quat.z * quat.z));
	mat.e[8] = 1 - (2 * (quat.x * quat.x)) - (2 * (quat.y * quat.y));

	mat.e[3] = (2 * (quat.x * quat.y)) - (2 * (quat.w * quat.z));
	mat.e[6] = (2 * (quat.x * quat.z)) + (2 * (quat.w * quat.y));

	mat.e[1] = (2 * (quat.x * quat.y)) + (2 * (quat.w * quat.z));
	mat.e[7] = (2 * (quat.y * quat.z)) - (2 * (quat.w * quat.x));

	mat.e[2] = (2 * (quat.x * quat.z)) - (2 * (quat.w * quat.y));
	mat.e[5] = (2 * (quat.y * quat.z)) + (2 * (quat.w * quat.x));

	*this *= mat;

	return *this;
}

Matrix3 Matrix3::Multiply(const Matrix3 &first, const Matrix3 &second)
{
	Matrix3 mat = Matrix3();

	mat.elements[0] = (first.e[0] * second.e[0]) + (first.e[3] * second.e[1]) + (first.e[6] * second.e[2]);
	mat.elements[1] = (first.e[1] * second.e[0]) + (first.e[4] * second.e[1]) + (first.e[7] * second.e[2]);
	mat.elements[2] = (first.e[2] * second.e[0]) + (first.e[5] * second.e[1]) + (first.e[8] * second.e[2]);

	mat.elements[3] = (first.e[0] * second.e[3]) + (first.e[3] * second.e[4]) + (first.e[6] * second.e[5]);
	mat.elements[4] = (first.e[1] * second.e[3]) + (first.e[4] * second.e[4]) + (first.e[7] * second.e[5]);
	mat.elements[5] = (first.e[2] * second.e[3]) + (first.e[5] * second.e[4]) + (first.e[8] * second.e[5]);

	mat.elements[6] = (first.e[0] * second.e[6]) + (first.e[3] * second.e[7]) + (first.e[6] * second.e[8]);
	mat.elements[7] = (first.e[1] * second.e[6]) + (first.e[4] * second.e[7]) + (first.e[7] * second.e[8]);
	mat.elements[8] = (first.e[2] * second.e[6]) + (first.e[5] * second.e[7]) + (first.e[8] * second.e[8]);

	return mat;
}

Matrix3 Matrix3::Divide(const Matrix3 &first, float second)
{
	Matrix3 temp;

	for (int i = 0; i < 9; i++)
		temp.e[i] = first.e[i] / second;

	return temp;
}

Matrix3 Matrix3::FromQuaternion(const Quaternion &quat)
{
	Matrix3 mat = Matrix3();

	mat.e[0] = 1 - (2 * (quat.y * quat.y)) - (2 * (quat.z * quat.z));
	mat.e[4] = 1 - (2 * (quat.x * quat.x)) - (2 * (quat.z * quat.z));
	mat.e[8] = 1 - (2 * (quat.x * quat.x)) - (2 * (quat.y * quat.y));

	mat.e[3] = (2 * (quat.x * quat.y)) - (2 * (quat.w * quat.z));
	mat.e[6] = (2 * (quat.x * quat.z)) + (2 * (quat.w * quat.y));

	mat.e[1] = (2 * (quat.x * quat.y)) + (2 * (quat.w * quat.z));
	mat.e[7] = (2 * (quat.y * quat.z)) - (2 * (quat.w * quat.x));

	mat.e[2] = (2 * (quat.x * quat.z)) - (2 * (quat.w * quat.y));
	mat.e[5] = (2 * (quat.y * quat.z)) + (2 * (quat.w * quat.x));

	return mat;
}

Quaternion Matrix3::ToQuaternion(const Matrix3 &mat)
{
	//---------TODO------------
	Quaternion quat = Quaternion();

	quat.w = sqrt((1 + mat.e[0] + mat.e[4] + mat.e[8]) / 2);
	float w4 = 4 * quat.w;
	quat.x = (mat.e[5] - mat.e[7]) / w4;
	quat.y = (mat.e[6] - mat.e[2]) / w4;
	quat.z = (mat.e[1] - mat.e[3]) / w4;

	return Quaternion();
}

std::ostream &operator<<(std::ostream &stream, const Matrix3 &mat)
{
	stream << mat.e[0] << ", " << mat.e[3] << ", " << mat.e[6] << ", " << std::endl <<
			  mat.e[1] << ", " << mat.e[4] << ", " << mat.e[7] << ", " << std::endl <<
			  mat.e[2] << ", " << mat.e[5] << ", " << mat.e[8] << std::endl;

	return stream;
}
