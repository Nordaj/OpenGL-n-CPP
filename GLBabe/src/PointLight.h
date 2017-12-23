#pragma once

#include "Math\Math.h"
#include "Light.h"

class PointLight : public Light 
{
public:
	Vector3 position;

	PointLight(Vector3 Position, Vector3 Color, float intensity);
	void PassPosition(unsigned int shader, std::string name);
	void PassAll(unsigned int shader, std::string positionName, std::string colorName, std::string intensityName);
};
