#include <glm\glm.hpp>
#include <glew.h>
#include <string>

#include "Light.h"
#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 Direction, glm::vec3 Position, glm::vec3 Color, float Intensity, float Cutoff)
{
	direction = Direction;
	position = Position;
	color = Color;
	intensity = Intensity;
	cutoff = Cutoff;
}

void SpotLight::PassDirection(unsigned int shader, std::string name)
{
	int pos = glGetUniformLocation(shader, name.c_str());
	glUniform3f(pos, direction.x, direction.y, direction.z);
}

void SpotLight::PassPosition(unsigned int shader, std::string name)
{
	int pos = glGetUniformLocation(shader, name.c_str());
	glUniform3f(pos, position.x, position.y, position.z);
}

void SpotLight::PassAll(unsigned int shader, std::string directionName, std::string positionName, std::string colorName, std::string intensityName, std::string cutoffName)
{
	//Direction
	int directionLocation = glGetUniformLocation(shader, directionName.c_str());
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);

	//Position
	int positionLocation = glGetUniformLocation(shader, positionName.c_str());
	glUniform3f(positionLocation, position.x, position.y, position.z);

	//Color
	int colorLocation = glGetUniformLocation(shader, colorName.c_str());
	glUniform3f(colorLocation, color.r, color.g, color.b);

	//Intensity
	int intensityLocation = glGetUniformLocation(shader, intensityName.c_str());
	glUniform1f(intensityLocation, intensity);

	//Cutoff
	int cutoffLocation = glGetUniformLocation(shader, cutoffName.c_str());
	glUniform1f(cutoffLocation, cutoff);
}
