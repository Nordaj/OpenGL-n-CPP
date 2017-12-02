#include <glm\glm.hpp>
#include <glew.h>
#include <string>
#include <vector>
#include <iostream>
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "UniformHandler.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

#include "LightManager.h"

LightManager::LightManager()
{ 
}

LightManager::LightManager(unsigned int Shader, bool DebugMode)
{
	shader = Shader;

	if (DebugMode)
	{
		debugRender = true;
		SetupDebug();
	}
}

LightManager::LightManager(unsigned int Shader, std::vector<DirectionalLight> DirectionalLights, std::vector<PointLight> PointLights, std::vector<SpotLight> SpotLights, glm::vec3 AmbientLight)
{
	shader = Shader;
	directionalLights = DirectionalLights;
	pointLights = PointLights;
	spotLights = SpotLights;
	ambientLight = AmbientLight;
}

void LightManager::SetupDebug()
{
	//Assign shader
	Shaders shaders = GrabShader("resources/Shaders/UnlitColor.shader");
	debugShader = CreateShader(shaders.Vertex, shaders.Fragment);
	glUseProgram(debugShader);

	debugCube = Transform();
	debugCube.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	debugCube.Translate(glm::vec3(0, 0, 0));
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

	//Spot Lights
	for (int i = 0; i < spotLights.size(); i++)
	{
		spotLights[i].PassAll(shader, "spotLight[" + std::to_string(i) + "].position",
									  "spotLight[" + std::to_string(i) + "].direction", 
									  "spotLight[" + std::to_string(i) + "].color",
									  "spotLight[" + std::to_string(i) + "].intensity",
									  "spotLight[" + std::to_string(i) + "].cutoff");
	}

	//Ambient Lights
	PassV3(shader, "uAmbient", ambientLight);
}

void LightManager::DrawDebug(Camera *camera, int cubeIndiciesLength)
{
	//Render unlit cube for debugging
	if (debugRender)
	{
		glUseProgram(debugShader);

		//Point Lights
		for (int i = 0; i < pointLights.size(); i++)
		{
			//Pass color
			PassV3(debugShader, "uColor", pointLights[i].color);

			//Set position of transform
			debugCube.SetPosition(pointLights[i].position);

			//MVP Matrix
			glm::mat4 model = debugCube.GetMatrix();
			glm::mat4 view = camera->GetView();
			glm::mat4 projection = camera->GetPerspective();
			glm::mat4 MVPMatrix = projection * view * model;

			//Give MVP to shader
			PassMat4(debugShader, "uMVPMatrix", MVPMatrix);

			//DRAW
			glDrawElements(GL_TRIANGLES, cubeIndiciesLength, GL_UNSIGNED_INT, nullptr);
		}

		//Spot Lights
		for (int i = 0; i < spotLights.size(); i++)
		{
			//Pass color
			PassV3(debugShader, "uColor", spotLights[i].color);

			//Set position of transform
			debugCube.SetPosition(spotLights[i].position);

			//MVP Matrix
			glm::mat4 model = debugCube.GetMatrix();
			glm::mat4 view = camera->GetView();
			glm::mat4 projection = camera->GetPerspective();
			glm::mat4 MVPMatrix = projection * view * model;

			//Give MVP to shader
			PassMat4(debugShader, "uMVPMatrix", MVPMatrix);

			//DRAW
			glDrawElements(GL_TRIANGLES, cubeIndiciesLength, GL_UNSIGNED_INT, nullptr);
		}
	}
}
