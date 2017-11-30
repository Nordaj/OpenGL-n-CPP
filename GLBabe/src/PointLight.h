#pragma once

class PointLight : public Light 
{
public:
	glm::vec3 position;

	PointLight(glm::vec3 Position, glm::vec3 Color, float intensity);
	void PassPosition(unsigned int shader, std::string name);
	void PassAll(unsigned int shader, std::string positionName, std::string colorName, std::string intensityName);
};
