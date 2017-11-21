#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\quaternion.hpp>
#include <iostream>
#include <cmath>

#include "Transform.h"

Transform::Transform ()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::mat4(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(glm::vec3 pos)
{
	position = pos;
	rotation = glm::mat4(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::mat4 Transform::GetMatrix()
{
	glm::mat4 transform = glm::mat4(1.0f);

	transform = glm::translate(transform, position);
	transform *= rotation;
	transform = glm::scale(transform, scale);

	return transform;
}

///Translate transform relative to current translation
void Transform::Translate(glm::vec3 translation)
{
	position += translation;
}

void Transform::Rotate(glm::vec3 dir, float amount)
{
	rotation = glm::rotate(rotation, glm::radians(amount), dir);
}

void Transform::Scale(glm::vec3 sc)
{
	scale += sc;
}
