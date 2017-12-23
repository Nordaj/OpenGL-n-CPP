#pragma once

#include <iostream>
#include <vector>
#include "Vector3.h"
#include "Quaternion.h"

//y * 4 + x

class Matrix4
{
public:
	float elements[16];

private:

public:
	Matrix4();
	Matrix4(float diagonal);
	Matrix4(std::vector<float> &Elements);

	Matrix4 Transpose();
	Matrix4 GetTransposed();

	Matrix4 Add(const float value);
	Matrix4 operator+(const float value);
	Matrix4 operator+=(const float value);

	Matrix4 Subtract(const float value);
	Matrix4 operator-(const float value);
	Matrix4 operator-=(const float value);

	Matrix4 Multiply(const Matrix4 &o);
	Matrix4 operator*(const Matrix4 &other);
	Matrix4 operator*=(const Matrix4 &other);

	Matrix4 Translate(const Vector3 &translation);
	Matrix4 Rotate(const Vector3 &axis, float angle);
	Matrix4 Rotate(Quaternion &quat);
	Matrix4 Scale(const Vector3 &scale);

	static Matrix4 TRS(Vector3 &translation, Quaternion &rotation, Vector3 &scale);
	static Matrix4 Orthagraphic(float right, float left, float top, float bottom, float near, float far);
	static Matrix4 Perspective(float fov, float aspect, float near, float far);

	friend std::ostream &operator<<(std::ostream &stream, const Matrix4 &mat);
};

//This matrix is collumn major meaning: 
/*
	{
	 0, 4, 8 , 12, 
	 1, 5, 9 , 13, 
	 2, 6, 10, 14, 
	 3, 7, 11, 15
	}
*/