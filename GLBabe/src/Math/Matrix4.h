#pragma once

#include <iostream>
#include "Vector3.h"

class Matrix4
{
public:
	float elements[16];

private:

public:
	Matrix4();
	Matrix4(float diagonal);

	Matrix4 Multiply(const Matrix4 other);
	Matrix4 operator*(const Matrix4 other);
	Matrix4 operator*=(const Matrix4 other);

	static Matrix4 Translation(Vector3 &translation);
	static Matrix4 Rotation(Vector3 &axis, float angle);
	static Matrix4 Scale(Vector3 &scale);
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