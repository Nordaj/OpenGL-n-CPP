#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0, 0, 3);
	lookAt = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);

	pov = 60;
	aspect = 1;
	near = 0.1f;
	far = 500;

	lookAtGlobal = false;
}

Camera::Camera(glm::vec3 Position, glm::vec3 LookAt, glm::vec3 Up, float Pov, float Aspect, float Near, float Far)
{
	position = Position;
	lookAt = LookAt;
	up = Up;

	pov = Pov;
	aspect = Aspect;
	near = Near;
	far = Far;

	lookAtGlobal = false;
}

glm::mat4 Camera::GetView()
{
	glm::mat4 view = glm::mat4(1.0f);

	if (lookAtGlobal)
		view = glm::lookAt(position, position + lookAt, up);
	else
		view = glm::lookAt(position, lookAt, up);

	return view;
}

glm::mat4 Camera::GetPerspective()
{
	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(pov), aspect, near, far);

	return projection;
}

void Camera::UpdateAspect(float Aspect)
{
	aspect = Aspect;
}