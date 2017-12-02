#pragma once

class SpotLight : public Light
{
public:
	glm::vec3 direction;
	glm::vec3 position;
	float cutoff;

	SpotLight(glm::vec3 Direction, glm::vec3 position, glm::vec3 Color, float Intensity, float cutoff);
	void PassDirection(unsigned int shader, std::string name);
	void PassPosition(unsigned int shader, std::string name);
	void PassAll(unsigned int shader, std::string directionName, std::string positionName, std::string colorName, std::string intensityName, std::string cutoffName);
};
