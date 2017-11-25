#pragma once

class PointLight : public Light 
{
public:
	glm::vec3 position;

	PointLight(glm::vec3 Position, glm::vec3 Color, float intensity);
	void PassPosition(unsigned int shader, const char* name);
	void PassAll(unsigned int shader, const char* positionName, const char* colorName, const char* intensityName);
};
