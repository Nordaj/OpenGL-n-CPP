#pragma once

#include "Math/Math.h"


class Transform 
{
public:
	Transform();
	Transform(Vector3 &pos);
	Matrix4 GetMatrix();
	void Translate(Vector3 &translation);
	void Transform::SetPosition(Vector3 &Position);
	void Rotate(Vector3 &dir, float amount);
	void Rotate(Vector3 &euler);
	void SetRotation(Quaternion &quat);
	void Scale(Vector3 &sc);
	void SetScale(Vector3 &sc);

private: 
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;
};
