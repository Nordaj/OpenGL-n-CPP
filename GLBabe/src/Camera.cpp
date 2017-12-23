//Includes
#include <iostream>

#include "Math/Math.h"

#include "Camera.h"

Camera::Camera()
{
	position = Vector3();
	rotation = Quaternion();

	fov = 60;
	aspect = 1;
	near = 0.1f;
	far = 500;

	view = Matrix4(1);
	projection = Matrix4(1);
}

Camera::Camera(Vector3 Position, float Fov, float Aspect, float Near, float Far)
{
	position = Position;
	rotation = Quaternion();

	fov = Fov;
	aspect = Aspect;
	near = Near;
	far = Far;

	view = Matrix4(1);
	projection = Matrix4(1);
}

void Camera::Rotate(Vector3 axis, float amount)
{
	rotation.Rotate(amount, axis);
}

Matrix4 Camera::GetView()
{
	view = Matrix4::TRS(position * -1, rotation, Vector3(1, 1, 1));

	return view;
}

Matrix4 Camera::GetProjection()
{
	projection = Matrix4::Perspective(fov, aspect, near, far);

	return projection;
}

void Camera::UpdateAspect(float Aspect)
{
	aspect = Aspect;
}