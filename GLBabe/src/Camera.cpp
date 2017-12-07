//Includes
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0, 1, 0);
	eulerAngles = glm::vec3(0, 0, 0);

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

	pov = Pov;
	aspect = Aspect;
	near = Near;
	far = Far;

	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
}

void Camera::RelativeTranslate(glm::vec3 translation)
{
	//TODO: Make relative to euler angles
	position += translation;
}

glm::mat4 Camera::GetView()
{
	glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, eulerAngles.x, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, eulerAngles.y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, eulerAngles.z, glm::vec3(0, 0, 1));

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