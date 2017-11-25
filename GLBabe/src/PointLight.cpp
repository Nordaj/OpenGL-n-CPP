#include <glm\glm.hpp>
#include <glew.h>

#include "Light.h"
#include "PointLight.h"

PointLight::PointLight(glm::vec3 Position, glm::vec3 Color, float Intensity)
{
	position = Position;
	color = Color;
	intensity = Intensity;
}

void PointLight::PassPosition(unsigned int shader, const char* name)
{
	int pos = glGetUniformLocation(shader, name);
	glUniform3f(pos, position.x, position.y, position.z);
}

void PointLight::PassAll(unsigned int shader, const char* positionName, const char* colorName, const char* intensityName)
{
	//Position
	int posLocation = glGetUniformLocation(shader, positionName);
	glUniform3f(posLocation, position.x, position.y, position.z);

	//Color
	int colLocation = glGetUniformLocation(shader, colorName);
	glUniform3f(colLocation, color.x, color.y, color.z);

	//Intensity
	int intLocation = glGetUniformLocation(shader, intensityName);
	glUniform1f(intLocation, intensity);
}
