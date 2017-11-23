#include <glm\glm.hpp>
#include <glew.h>

#include "Light.h"

Light::Light()
{
	position = glm::vec3(0, 0, 0);
	color = glm::vec3(1, 0, 0);
	intensity = 1;
}

Light::Light(glm::vec3 Position, glm::vec3 Color, float Intensity)
{
	position = Position;
	color = Color;
	intensity = Intensity;
}

void Light::PassPosition(unsigned int shader, const char* name)
{
	int pos = glGetUniformLocation(shader, name);
	glUniform3f(pos, position.x, position.y, position.z);
}

void Light::PassColor(unsigned int shader, const char* name)
{
	int col = glGetUniformLocation(shader, name);
	glUniform3f(col, color.x, color.y, color.z);
}

void Light::PassIntensity(unsigned int shader, const char* name)
{
	int in = glGetUniformLocation(shader, name);
	glUniform1f(in, intensity);
}
