#pragma once

class Light 
{
public: 
	glm::vec3 color;
	float intensity;

	Light();
	void PassColor(unsigned int shader, const char* name);
	void PassIntensity(unsigned int shader, const char* name);
};
