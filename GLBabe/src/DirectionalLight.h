#pragma once

#include <string>

#include "Math\Math.h"
#include "Light.h"

class DirectionalLight : public Light
{
public:
	Vector3 direction;

	DirectionalLight(Vector3 Direction, Vector3 Color, float Intensity);
	void PassDirection(unsigned int shader, std::string name);
	void PassAll(unsigned int shader, std::string directionName, std::string colorName, std::string intensityName);
};
