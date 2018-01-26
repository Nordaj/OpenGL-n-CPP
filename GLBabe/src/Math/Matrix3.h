#pragma once

#include <iostream>
#include <vector>

#include "Quaternion.h"
#include "Matrix4.h"

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
	//Constructors
	Matrix3();
	Matrix3(float diagonal);
	Matrix3(const std::vector<float> &e);
	Matrix3(const Quaternion &quat);

	//Extra
	float GetDeterminant() const;
	bool IsOtho() const;

	Vector3 GetCollumn(int id) const;
	Vector3 GetRow(int id) const;

	//Basic functions
	Matrix3 Transpose();
	Matrix3 GetTransposed() const;

	Matrix3 Invert();
	Matrix3 Inverse() const;

	//Relative functions
	Matrix3 Rotate(const Vector3 &axis, float angle);
	Matrix3 Rotate(const Quaternion &quat);

	//Relative conversions
	Quaternion ToQuaternion() const;

	//Basic operations
	Matrix3 Multiply(const Matrix3 &other);
	Matrix3 operator*(const Matrix3 &other) const;
	Matrix3 operator*=(const Matrix3 &other);

	Matrix3 Divide(float other);
	Matrix3 operator/(float other) const;
	Matrix3 operator/=(float other);

	Vector3 Multiply(const Vector3 &v) const;
	Vector3 operator*(const Vector3 &v) const;

	bool operator==(const Matrix3 &second);

	//Static operations
	static Matrix3 Multiply(const Matrix3 &first, const Matrix3 &second);
	static Matrix3 Divide(const Matrix3 &first, float second);
	static Vector3 Multiply(const Vector3 &v, const Matrix3 &m);

	//Static convertions
	static Matrix3 FromQuaternion(const Quaternion &quat);
	static Quaternion ToQuaternion(const Matrix3 &mat);
	static Matrix3 FromAxisAngle(const Vector3 &axis, float angle);
	static Matrix3 FromEuler(const Vector3 &euler);
	static Matrix4 ToMat4(const Matrix3 &mat);

	//Friend
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

	-first num = collumn, second = row (some website with head up ass)
	m00	m10	m20
	m01	m11	m21
	m02	m12	m22
}
*/
