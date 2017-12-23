#pragma once

#include <string>

#include "Math\Math.h"
#include "Light.h"

class SpotLight : public Light
{
public:
	Vector3 direction;
	Vector3 position;
	float cutoff;

	SpotLight(Vector3 Direction, Vector3 position, Vector3 Color, float Intensity, float cutoff);
	void PassDirection(unsigned int shader, std::string name);
	void PassPosition(unsigned int shader, std::string name);
	void PassAll(unsigned int shader, std::string directionName, std::string positionName, std::string colorName, std::string intensityName, std::string cutoffName);
};
