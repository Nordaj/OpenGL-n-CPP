#pragma once

class LightManager
{
public:
	unsigned int shader;
	std::vector<DirectionalLight> directionalLights;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;
	glm::vec3 ambientLight;

	LightManager();
	LightManager(unsigned int Shader, bool DebugMode = false);
	LightManager(unsigned int Shader, std::vector<DirectionalLight> DirectionalLights, std::vector<PointLight> PointLights, std::vector<SpotLight> SpotLights, glm::vec3 AmbientLight);
	void UpdateLighting(float deltaTime);
	void DrawDebug(Camera *camera, int cubeIndiciesLength);

private:
	bool debugRender;
	unsigned int debugShader;
	Transform debugCube;

	//cubeIndiciesLength is hopefully temp, as of now im sharing the same cube model, change later
	void SetupDebug();
};
