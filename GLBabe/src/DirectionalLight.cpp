#include <glew.h>
#include <string>

#include "Light.h"
#include "Math\Math.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3 Direction, Vector3 Color, float Intensity)
{
	direction = Direction;
	color = Color;
	intensity = Intensity;
}

void DirectionalLight::PassDirection(unsigned int shader, std::string name)
{
	int pos = glGetUniformLocation(shader, name.c_str());
	glUniform3f(pos, direction.x, direction.y, direction.z);
}

void DirectionalLight::PassAll(unsigned int shader, std::string directionName, std::string colorName, std::string intensityName)
{
	//Direction
	int dirLocation = glGetUniformLocation(shader, directionName.c_str());
	glUniform3f(dirLocation, direction.x, direction.y, direction.z);

	//Color
	int colLocation = glGetUniformLocation(shader, colorName.c_str());
	glUniform3f(colLocation, color.x, color.y, color.z);

	//Intensity
	int intLocation = glGetUniformLocation(shader, intensityName.c_str());
	glUniform1f(intLocation, intensity);
}
