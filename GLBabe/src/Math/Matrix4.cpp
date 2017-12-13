#include <iostream>
#include <math.h>
#include <vector>

#include "Misc.h"
#include "Vector3.h"

#include "Matrix4.h"

Matrix4::Matrix4()
{
	//Create identity matrix
	elements[0] = 1;
	elements[5] = 1;
	elements[10] = 1;
	elements[15] = 1;

	//The others
	elements[1] = 0;
	elements[2] = 0;
	elements[3] = 0;
	elements[4] = 0;

	elements[6] = 0;
	elements[7] = 0;
	elements[8] = 0;
	elements[9] = 0;

	elements[11] = 0;
	elements[12] = 0;
	elements[13] = 0;
	elements[14] = 0;
}

Matrix4::Matrix4(float diagonal)
{
	//Create identity matrix
	elements[0] = diagonal;
	elements[5] = diagonal;
	elements[10] = diagonal;
	elements[15] = diagonal;

	//The others
	elements[1] = 0;
	elements[2] = 0;
	elements[3] = 0;
	elements[4] = 0;

	elements[6] = 0;
	elements[7] = 0;
	elements[8] = 0;
	elements[9] = 0;

	elements[11] = 0;
	elements[12] = 0;
	elements[13] = 0;
	elements[14] = 0;
}

Matrix4::Matrix4(std::vector<float> &Elements)
{
	for (int i = 0; i < 16; i++)
		elements[i] = Elements[i];
}

Matrix4 Matrix4::Transpose()
{
	Matrix4 OG = *this;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			elements[x * 4 + y] = OG.elements[y * 4 + x];
		}
	}

	return *this;
}

Matrix4 Matrix4::GetTransposed()
{
	Matrix4 mat;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			mat.elements[x * 4 + y] = elements[y * 4 + x];
		}
	}

	return mat;
}

Matrix4 Matrix4::Add(const float value)
{
	Matrix4 mat = Matrix4();

	for (int i = 0; i < sizeof(mat.elements) / sizeof(float); i++)
		mat.elements[i] = elements[i] + value;

	return mat;
}

Matrix4 Matrix4::operator+(const float value)
{
	return this->Add(value);
}

Matrix4 Matrix4::operator+=(const float value)
{
	for (int i = 0; i < sizeof(elements) / sizeof(float); i++)
		elements[i] += value;

	return *this;
}

Matrix4 Matrix4::Subtract(const float value)
{
	Matrix4 mat = Matrix4();

	for (int i = 0; i < sizeof(mat.elements) / sizeof(float); i++)
		mat.elements[i] = elements[i] - value;

	return mat;
}

Matrix4 Matrix4::operator-(const float value)
{
	return this->Subtract(value);
}

Matrix4 Matrix4::operator-=(const float value)
{
	for (int i = 0; i < sizeof(elements) / sizeof(float); i++)
		elements[i] -= value;

	return *this;
}

Matrix4 Matrix4::Multiply(const Matrix4 other)
{
	Matrix4 mat = Matrix4(0.0f);

	//Row
	for (int y = 0; y < 4; y++)
	{
		//Communn
		for (int x = 0; x < 4; x++)
		{
			//Go accross for second one
			float sum = 0;
			for (int i = 0; i < 4; i++)
			{
				sum += elements[i * 4 + x] * other.elements[y * 4 + i];
			}
			mat.elements[y * 4 + x] = sum;
		}
	}

	return mat;
}

Matrix4 Matrix4::operator*(const Matrix4 other)
{
	return this->Multiply(other);
}

Matrix4 Matrix4::operator*=(const Matrix4 other)
{
	*this = this->Multiply(other);
	return *this;
}

Matrix4 Matrix4::Translate(const Vector3 &translation)
{
	elements[12] = translation.x;
	elements[13] = translation.y;
	elements[14] = translation.z;

	return *this;
}

Matrix4 Matrix4::Rotate(const Vector3 &axis, float angle)
{
	//MIGHT NOT WORK
	//(did not match glm or an online rotation calc, we shall see if this works)

	angle = Radians(angle);

	float c = cos(angle);
	float s = sin(angle);

	elements[0]  = axis.x * axis.x * ((1 - c) + c);
	elements[5]  = axis.y * axis.y * ((1 - c) + c);
	elements[10] = axis.z * axis.z * ((1 - c) + c);

	elements[1] = (axis.x * axis.y) * (1 - c) + (axis.z * s);
	elements[2] = (axis.x * axis.z) * (1 - c) - (axis.y * s);

	elements[4] = (axis.y * axis.x) * (1 - c) - (axis.z * s);
	elements[6] = (axis.y * axis.z) * (1 - c) + (axis.x * s);

	elements[8] = (axis.z * axis.x) * (1 - c) + (axis.y * s);
	elements[9] = (axis.z * axis.y) * (1 - c) - (axis.x * s);

	return *this;
}

Matrix4 Matrix4::Scale(const Vector3 &scale)
{
	elements[0] = scale.x;
	elements[5] = scale.y;
	elements[10] = scale.z;

	return *this;
}

Matrix4 Matrix4::Orthagraphic(float right, float left, float top, float bottom, float near, float far)
{
	Matrix4 mat = Matrix4(1);

	//Diagonal
	mat.elements[0] = 2 / (right - left);
	mat.elements[5] = 2 / (top - bottom);
	mat.elements[10] = -2 / (far - near);

	//Right stuff
	mat.elements[12] = -((right + left) / (right - left));
	mat.elements[13] = -((top + bottom) / (top - bottom));
	mat.elements[14] = (-(far + near) / (far - near));

	return mat;
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float near, float far)
{
	Matrix4 mat = Matrix4(0);

	mat.elements[0] = 1 / (aspect * tan(Radians(fov) / 2));
	mat.elements[5] = 1 / (tan(Radians(fov) / 2));
	mat.elements[10] = -((far + near) / (far - near));
	mat.elements[14] = -((2 * far * near) / (far - near));
	mat.elements[11] = -1;

	return mat;
}

std::ostream &operator<<(std::ostream &stream, const Matrix4 &mat)
{
	stream <<
		mat.elements[0] << ", " << mat.elements[4] << ", " << mat.elements[8] << ", " << mat.elements[12] << std::endl <<
		mat.elements[1] << ", " << mat.elements[5] << ", " << mat.elements[9] << ", " << mat.elements[13] << std::endl <<
		mat.elements[2] << ", " << mat.elements[6] << ", " << mat.elements[10] << ", " << mat.elements[14] << std::endl <<
		mat.elements[3] << ", " << mat.elements[7] << ", " << mat.elements[11] << ", " << mat.elements[15] << std::endl;

	return stream;
}
