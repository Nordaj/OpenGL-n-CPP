#pragma once

#include <vector>
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Math\Math.h"
#include "Transform.h"

class LightManager
{
public:
	std::vector<DirectionalLight> directionalLights;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;
	Vector3 ambientLight;

	LightManager();
	LightManager(unsigned int Shader, bool DebugMode = false);
	LightManager(unsigned int Shader, std::vector<DirectionalLight> DirectionalLights, std::vector<PointLight> PointLights, std::vector<SpotLight> SpotLights, Vector3 AmbientLight, bool DebugMode = true);
	void UpdateLighting(unsigned int shad = -1);
	void DrawDebug(Matrix4 view, Matrix4 projection);

private:
	bool debugRender;
	unsigned int debugShader;
	unsigned int debugVAO;
	unsigned int debugVBO;
	unsigned int debugIBO;
	Transform transform;
	unsigned int shader;

	void SetupDebug();
};
