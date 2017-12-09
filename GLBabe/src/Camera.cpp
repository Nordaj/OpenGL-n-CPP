//Includes
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\quaternion.hpp>
#include <iostream>

#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0, 1, 0);
	rotation = glm::quat();
	rotation.w = 1;

	pov = 60;
	aspect = 1;
	near = 0.1f;
	far = 500;

	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
}

Camera::Camera(glm::vec3 Position, float Pov, float Aspect, float Near, float Far)
{
	position = Position;
	rotation = glm::quat();

	pov = Pov;
	aspect = Aspect;
	near = Near;
	far = Far;

	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
}

void Camera::Rotate(glm::vec3 axis, float amount)
{
	amount = glm::radians(amount);

	glm::quat change = glm::quat();
	change.w = 1;

	change.x = axis.x * sin(amount / 2);
	change.y = axis.y * sin(amount / 2);
	change.z = axis.z * sin(amount / 2);
	change.w = cos(amount / 2);

	rotation = change * rotation;

	//rotation = glm::rotate(rotation, glm::radians(amount), axis);

	/* PSEUDO CODE FROM ONLINE
	x = RotationAxis.x * sin(RotationAngle / 2)
	y = RotationAxis.y * sin(RotationAngle / 2)
	z = RotationAxis.z * sin(RotationAngle / 2)
	w = cos(RotationAngle / 2)
	*/
}

glm::mat4 Camera::GetView()
{
	//glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 rot = glm::toMat4(rotation);

	view = glm::mat4(1.0f);
	view *= rot;
	view = glm::translate(view, -position);
	return view;
}

glm::mat4 Camera::GetProjection()
{
	projection = glm::perspective(glm::radians(pov), aspect, near, far);

	return projection;
}

void Camera::UpdateAspect(float Aspect)
{
	aspect = Aspect;
}