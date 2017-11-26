#include <glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "UniformHandler.h"

void PassFloat(int shader, const char* name, float value)
{
	int FOO = glGetUniformLocation(shader, name);
	glUniform1f(FOO, value);
}

void PassInt(int shader, const char* name, int value)
{
	int FOO = glGetUniformLocation(shader, name);
	glUniform1i(FOO, value);
}

void PassV3(int shader, const char* name, glm::vec3 value)
{
	int FOO = glGetUniformLocation(shader, name);
	glUniform3f(FOO, value.x, value.y, value.z);
}

void PassV4(int shader, const char* name, glm::vec4 value)
{
	int FOO = glGetUniformLocation(shader, name);
	glUniform4f(FOO, value.x, value.y, value.z, value.w);
}

void PassMat4(int shader, const char* name, glm::mat4 value)
{
	int FOO = glGetUniformLocation(shader, name);
	glUniformMatrix4fv(FOO, 1, GL_FALSE, glm::value_ptr(value));
}
