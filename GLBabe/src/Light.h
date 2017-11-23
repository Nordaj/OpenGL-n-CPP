#pragma once

class Light 
{
public: 
	glm::vec3 position;
	glm::vec3 color;
	float intensity;

	Light();
	Light(glm::vec3 Position, glm::vec3 Color, float Intensity);
	void PassPosition(unsigned int shader, const char* name);
	void PassColor(unsigned int shader, const char* name);
	void PassIntensity(unsigned int shader, const char* name);
};
