#pragma once

#include <string>

#include "Math\Math.h"

class Light 
{
public: 
	Vector3 color;
	float intensity;

	Light();
	void PassColor(unsigned int shader, std::string name);
	void PassIntensity(unsigned int shader, std::string name);
};
