#pragma once

class DirectionalLight : public Light
{
public:
	glm::vec3 direction;

	DirectionalLight(glm::vec3 Direction, glm::vec3 Color, float Intensity);
	void PassDirection(unsigned int shader, const char* name);
	void PassAll(unsigned int shader, const char* directionName, const char* colorName, const char* intensityName);
};
