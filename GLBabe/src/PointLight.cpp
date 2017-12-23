#include <glew.h>
#include <string>

#include "Math\Math.h"
#include "Light.h"
#include "PointLight.h"

PointLight::PointLight(Vector3 Position, Vector3 Color, float Intensity)
{
	position = Position;
	color = Color;
	intensity = Intensity;
}

void PointLight::PassPosition(unsigned int shader, std::string name)
{
	int pos = glGetUniformLocation(shader, name.c_str());
	glUniform3f(pos, position.x, position.y, position.z);
}

void PointLight::PassAll(unsigned int shader, std::string positionName, std::string colorName, std::string intensityName)
{
	//Position
	int posLocation = glGetUniformLocation(shader, positionName.c_str());
	glUniform3f(posLocation, position.x, position.y, position.z);

	//Color
	int colLocation = glGetUniformLocation(shader, colorName.c_str());
	glUniform3f(colLocation, color.x, color.y, color.z);

	//Intensity
	int intLocation = glGetUniformLocation(shader, intensityName.c_str());
	glUniform1f(intLocation, intensity);
}
