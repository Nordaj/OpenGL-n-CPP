#pragma once

#include <iostream>
#include <vector>

#include "Quaternion.h"

class Matrix3 
{
public:
	//Wierd thing to do but i wanted shorter syntax while keeping nice options
	union 
	{
		float elements[9];

		float e[9];

		struct 
		{
			float m00, m10, m20, m01, m11, m21, m02, m12, m22;
		};
	};

private:

public:
	Matrix3();
	Matrix3(float diagonal);
	Matrix3(const std::vector<float> &e);
	Matrix3(const Quaternion &quat);

	float GetDeterminant() const;

	Matrix3 Transpose();
	Matrix3 GetTransposed() const;

	Matrix3 Invert();
	Matrix3 Inverse() const;

	Matrix3 Multiply(const Matrix3 &other);
	Matrix3 operator*(const Matrix3 &other) const;
	Matrix3 operator*=(const Matrix3 &other);

	Matrix3 Divide(float other);
	Matrix3 operator/(float other) const;
	Matrix3 operator/=(float other);

	Matrix3 Rotate(const Vector3 &axis, float angle);
	Matrix3 Rotate(const Quaternion &quat);

	static Matrix3 Multiply(const Matrix3 &first, const Matrix3 &second);
	static Matrix3 Divide(const Matrix3 &first, float second);
	static Matrix3 FromQuaternion(const Quaternion &quat);
	static Quaternion ToQuaternion(const Matrix3 &mat);

	friend std::ostream &operator<<(std::ostream &stream, const Matrix3 &mat);
};

typedef Matrix3 RotationMatrix;

//This matrix is collumn major meaning: 
/*
{
	0, 3, 6,
	1, 4, 7,
	2, 5, 8

	-First num = row, second = collumn (f. of engine book) (me)
	m00	m01	m02
	m10	m11	m12
	m20	m21	m22

	-first num = collumn, second = row
	m00	m10	m20
	m01	m11	m21
	m02	m12	m22
}
*/
