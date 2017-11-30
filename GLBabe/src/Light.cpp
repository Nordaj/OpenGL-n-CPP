#include <glm\glm.hpp>
#include <glew.h>
#include <string>

#include "Light.h"

Light::Light()
{
	color = glm::vec3(1, 0, 0);
	intensity = 1;
}

void Light::PassColor(unsigned int shader, std::string name)
{
	int col = glGetUniformLocation(shader, name.c_str());
	glUniform3f(col, color.x, color.y, color.z);
}

void Light::PassIntensity(unsigned int shader, std::string name)
{
	int in = glGetUniformLocation(shader, name.c_str());
	glUniform1f(in, intensity);
}
