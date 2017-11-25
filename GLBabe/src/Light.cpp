#include <glm\glm.hpp>
#include <glew.h>

#include "Light.h"

Light::Light()
{
	color = glm::vec3(1, 0, 0);
	intensity = 1;
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
