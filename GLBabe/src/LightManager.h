#pragma once

class LightManager
{
public:
	unsigned int shader;
	std::vector<DirectionalLight> directionalLights;
	std::vector<PointLight> pointLights;
	glm::vec3 ambientLight;

	LightManager();
	LightManager(unsigned int Shader);
	LightManager(unsigned int Shader, std::vector<DirectionalLight> DirectionalLights, std::vector<PointLight> PointLights, glm::vec3 AmbientLight);
	void UpdateLighting(float deltaTime);
};
