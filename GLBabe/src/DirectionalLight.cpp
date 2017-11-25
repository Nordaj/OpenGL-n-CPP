#include <glm\glm.hpp>
#include <glew.h>

#include "Light.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 Direction, glm::vec3 Color, float Intensity)
{
	direction = Direction;
	color = Color;
	intensity = Intensity;
}

void DirectionalLight::PassDirection(unsigned int shader, const char* name)
{
	int pos = glGetUniformLocation(shader, name);
	glUniform3f(pos, direction.x, direction.y, direction.z);
}

void DirectionalLight::PassAll(unsigned int shader, const char* directionName, const char* colorName, const char* intensityName)
{
	//Direction
	int dirLocation = glGetUniformLocation(shader, directionName);
	glUniform3f(dirLocation, direction.x, direction.y, direction.z);

	//Color
	int colLocation = glGetUniformLocation(shader, colorName);
	glUniform3f(colLocation, color.x, color.y, color.z);

	//Intensity
	int intLocation = glGetUniformLocation(shader, intensityName);
	glUniform1f(intLocation, intensity);
}
