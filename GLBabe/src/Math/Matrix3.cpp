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
	return m00 * (m11 * m22 - m12 * m21) + 
		   m01 * (m12 * m20 - m10 * m22) + 
		   m02 * (m10 * m21 - m11 * m20);
}

bool Matrix3::IsOtho() const
{
	Matrix3 m1 = Inverse();
	Matrix3 m2 = GetTransposed();
	return (m1 == m2);
}

Vector3 Matrix3::GetCollumn(int id) const
{
	//Input ranges from 0-2
	int foo = id * 3;
	return Vector3(e[foo], e[foo] + 1, e[foo] + 2);
}

Vector3 Matrix3::GetRow(int id) const
{
	//Input ranges from 0-2
	return Vector3(e[id], e[id + 3], e[id + 6]);
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

Matrix3 Matrix3::Rotate(const Vector3 &axis, float angle)
{
	/* ---This method does not keep determinate as 1---
	Matrix3 mat = Matrix3();
	Vector3 a = axis.Normalized();

	angle = Radians(angle);

	float c = cos(angle);
	float s = sin(angle);

	mat.e[0] = a.x * a.x * ((1 - c) + c);
	mat.e[4] = a.y * a.y * ((1 - c) + c);
	mat.e[8] = a.z * a.z * ((1 - c) + c);

	mat.e[1] = (a.x * a.y) * (1 - c) + (a.z * s);
	mat.e[2] = (a.x * a.z) * (1 - c) - (a.z * s);

	mat.e[3] = (a.y * a.x) * (1 - c) - (a.z * s);
	mat.e[5] = (a.y * a.z) * (1 - c) + (a.x * s);

	mat.e[6] = (a.z * a.x) * (1 - c) + (a.y * s);
	mat.e[7] = (a.y * a.z) * (1 - c) - (a.x * s);

	*this *= mat;

	return *this;
	*/

	//---Algorithm from Foundations of Game Engine Development, pg 64, written differently---

	Matrix3 mat = Matrix3();
	Vector3 a = axis.Normalized();

	angle = Radians(angle);

	float c = cos(angle);
	float s = sin(angle);
	float mc = 1 - c;

	float x = a.x * mc;
	float y = a.y * mc;
	float z = a.z * mc;
	float xy = x * a.y;
	float xz = x * a.z;
	float yz = y * a.z;

	mat.m00 = c + x * a.x;
	mat.m11 = c + y * a.y;
	mat.m22 = c + z * a.z;

	mat.m10 = xy + s * a.z;
	mat.m20 = xz - s * a.y;

	mat.m01 = xy - s * a.z;
	mat.m21 = yz + s * a.x;

	mat.m02 = xz + s * a.y;
	mat.m12 = yz - s * a.x;

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

Quaternion Matrix3::ToQuaternion() const
{
	return ToQuaternion(*this);
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

bool Matrix3::operator==(const Matrix3 &second)
{
	for (int i = 0; i < 9; i++)
		if (!FComp(e[i], second.e[i])) return false;

	return true;
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
	//---Algorithm from Foundations of Game Engine Development (pg 93), written differently---

	//Check Determinant
	float det = mat.GetDeterminant();
	if (!(fabs(det - 1) < 0.0001f))  return Quaternion();

	//Check Orthogonal (not working)
	if (!mat.IsOtho()) return Quaternion();

	//Get sum of diagonal
	float sum = mat.m00 + mat.m11 + mat.m22;

	Quaternion quat;
	if (sum > 0)
	{
		//Positive diag
		quat.w = sqrt(sum + 1) * 0.5f;
		float f = 0.25f / quat.w;
		quat.x = (mat.m21 - mat.m12) * f;
		quat.y = (mat.m02 - mat.m20) * f;
		quat.z = (mat.m10 - mat.m01) * f;
	}
	else if ((mat.m00 > mat.m11) && (mat.m00 > mat.m22))
	{
		//Top left is largest diag
		quat.x = sqrt(mat.m00 - mat.m11 - mat.m22 + 1) * 0.5f;
		float f = 0.25f / quat.x;
		quat.y = (mat.m10 + mat.m01) * f;
		quat.z = (mat.m02 + mat.m20) * f;
		quat.w = (mat.m21 - mat.m12) * f;
	}
	else if (mat.m11 > mat.m22)
	{
		//M11 is the largest diag
		quat.y = sqrt(mat.m00 - mat.m11 - mat.m22 + 1) * 0.5f;
		float f = 0.25f / quat.y;
		quat.x = (mat.m01 + mat.m10) * f;
		quat.z = (mat.m21 + mat.m12) * f;
		quat.w = (mat.m02 - mat.m20) * f;
	}
	else
	{
		//M22 is the largest diag
		quat.z = sqrt(mat.m00 - mat.m11 - mat.m22 + 1) * 0.5f;
		float f = 0.25f / quat.z;
		quat.x = (mat.m20 + mat.m02) * f;
		quat.y = (mat.m21 + mat.m12) * f;
		quat.w = (mat.m10 - mat.m01) * f;
	}

	return quat;
}

Matrix3 Matrix3::FromAxisAngle(const Vector3 &axis, float angle)
{
	Matrix3 mat = Matrix3();
	Vector3 a = axis.Normalized();

	angle = Radians(angle);

	float c = cos(angle);
	float s = sin(angle);
	float mc = 1 - c;

	float x = a.x * mc;
	float y = a.y * mc;
	float z = a.z * mc;
	float xy = x * a.y;
	float xz = x * a.z;
	float yz = y * a.z;

	mat.m00 = c + x * a.x;
	mat.m11 = c + y * a.y;
	mat.m22 = c + z * a.z;

	mat.m10 = xy + s * a.z;
	mat.m20 = xz - s * a.y;

	mat.m01 = xy - s * a.z;
	mat.m21 = yz + s * a.x;

	mat.m02 = xz + s * a.y;
	mat.m12 = yz - s * a.x;

	return mat;
}

Matrix3 Matrix3::FromEuler(const Vector3 &euler)
{
	//http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToMatrix/index.htm

	Matrix3 mat;

	float sx = sin(Radians(euler.x)); //sb
	float sy = sin(Radians(euler.y)); //sh
	float sz = sin(Radians(euler.z)); //sa
	float cx = cos(Radians(euler.x)); //cb
	float cy = cos(Radians(euler.y)); //ch
	float cz = cos(Radians(euler.z)); //ca

	mat.m00 = cy * cz;
	mat.m01 = -cy * sz * cx + sy * sx;
	mat.m02 = cy * sz * sx + sy * cx;

	mat.m10 = sz;
	mat.m11 = cz * cx;
	mat.m12 = -cz * sx;

	mat.m20 = -sy * cz;
	mat.m21 = sy * sz * cx + cy * sx;
	mat.m22 = -sy * sz * sx + cy * cx;

	return mat;

	/*
	Matrix3 rotX = Matrix3();
	Matrix3 rotY = Matrix3();
	Matrix3 rotZ = Matrix3();

	rotX.m11 = cos(Radians(euler.x));
	rotX.m12 = -sin(Radians(euler.x));
	rotX.m21 = sin(Radians(euler.x));
	rotX.m22 = cos(Radians(euler.x));

	rotY.m00 = cos(Radians(euler.y));
	rotY.m20 = -sin(Radians(euler.y));
	rotY.m22 = cos(Radians(euler.y));
	rotY.m02 = sin(Radians(euler.y));

	rotZ.m00 = cos(Radians(euler.z));
	rotZ.m10 = sin(Radians(euler.z));
	rotZ.m11 = cos(Radians(euler.z));
	rotZ.m01 = -sin(Radians(euler.z));

	//I think this means X->Y->Z because matrix multiplication is backwards. (may be wrong)
	return rotX * rotY * rotZ;
	*/
}

std::ostream &operator<<(std::ostream &stream, const Matrix3 &mat)
{
	stream << mat.e[0] << ", " << mat.e[3] << ", " << mat.e[6] << ", " << std::endl <<
			  mat.e[1] << ", " << mat.e[4] << ", " << mat.e[7] << ", " << std::endl <<
			  mat.e[2] << ", " << mat.e[5] << ", " << mat.e[8] << std::endl;

	return stream;
}
