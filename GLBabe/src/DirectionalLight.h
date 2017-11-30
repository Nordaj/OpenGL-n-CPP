#pragma once

class DirectionalLight : public Light
{
public:
	glm::vec3 direction;

	DirectionalLight(glm::vec3 Direction, glm::vec3 Color, float Intensity);
	void PassDirection(unsigned int shader, std::string name);
	void PassAll(unsigned int shader, std::string directionName, std::string colorName, std::string intensityName);
};
