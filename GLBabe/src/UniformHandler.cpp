#include <glew.h>

#include "Math\Math.h"
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

void PassV3(int shader, const char* name, Vector3 &value)
{
	int FOO = glGetUniformLocation(shader, name);
	glUniform3f(FOO, value.x, value.y, value.z);
}

void PassV4(int shader, const char* name, Vector4 &value)
{
	int FOO = glGetUniformLocation(shader, name);
	glUniform4f(FOO, value.x, value.y, value.z, value.w);
}

void PassMat4(int shader, const char* name, Matrix4 &value)
{
	int FOO = glGetUniformLocation(shader, name);
	glUniformMatrix4fv(FOO, 1, GL_FALSE, &value.elements[0]);
}
