#include <glm\glm.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "UniformHandler.h"

#include "LightManager.h"

LightManager::LightManager()
{ }

LightManager::LightManager(unsigned int Shader)
{
	shader = Shader;
}

LightManager::LightManager(unsigned int Shader, std::vector<DirectionalLight> DirectionalLights, std::vector<PointLight> PointLights, glm::vec3 AmbientLight)
{
	shader = Shader;
	directionalLights = DirectionalLights;
	pointLights = PointLights;
	ambientLight = AmbientLight;
}

void LightManager::UpdateLighting(float deltaTime)
{
	//Directional Lights
	for (int i = 0; i < directionalLights.size(); i++)
	{
		directionalLights[i].PassAll(shader, "directionalLight[" + std::to_string(i) + "].direction",
											 "directionalLight[" + std::to_string(i) + "].color",
											 "directionalLight[" + std::to_string(i) + "].intensity");
	}

	//Point Lights
	for (int i = 0; i < pointLights.size(); i++)
	{
		pointLights[i].PassAll(shader, "pointLight[" + std::to_string(i) + "].position",
									   "pointLight[" + std::to_string(i) + "].color",
									   "pointLight[" + std::to_string(i) + "].intensity");
	}

	//Ambient Lights
	PassV3(shader, "uAmbient", ambientLight);

	//TODO: Render light as unlit cube mesh
}
