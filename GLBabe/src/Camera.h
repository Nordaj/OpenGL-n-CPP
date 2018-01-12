#pragma once

#include "Math/Math.h"

class Camera
{
public:
	Vector3 position;
	Quaternion rotation;

	Camera();
	Camera(Vector3 Position, float Fov = 60, float Aspect = 1, float Near = 0.1f, float Far = 500);
	Matrix4 GetView();
	Matrix4 GetProjection();
	void UpdateAspect(float aspect);
	void Rotate(Vector3 &axis, float amount);
	void Rotate(Vector3 &euler);

private: 
	bool first;
	float fov;
	float aspect;
	float near;
	float far;
	Matrix4 view;
	Matrix4 projection;
};
