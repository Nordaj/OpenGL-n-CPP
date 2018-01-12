#include <iostream>
#include <cmath>

#include "Math\Math.h"
#include "Transform.h"

Transform::Transform()
{
	position = Vector3();
	rotation = Quaternion();
	scale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(Vector3 &pos)
{
	position = pos;
	rotation = Quaternion();
	scale = Vector3(1, 1, 1);
}

Matrix4 Transform::GetMatrix()
{
	Matrix4 transform = Matrix4::TRS(position, rotation, scale);

	return transform;
}

void Transform::Translate(Vector3 &translation)
{
	position += translation;
}

void Transform::SetPosition(Vector3 &Position)
{
	position = Position;
}

void Transform::Rotate(Vector3 &dir, float amount)
{
	rotation.Rotate(dir, amount);
}

void Transform::Rotate(Vector3 &euler)
{
	rotation.Rotate(euler);
}

void Transform::SetRotation(Quaternion &quat)
{
	rotation = quat;
}

void Transform::Scale(Vector3 &sc)
{
	scale *= sc;
}

void Transform::SetScale(Vector3 &sc)
{
	scale = sc;
}