#include <glew.h>
#include <string>
#include <vector>
#include <iostream>
#include "Light.h"
#include "UniformHandler.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "HardCodedMeshes.h"

#include "Math\Math.h"
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

LightManager::LightManager(unsigned int Shader, std::vector<DirectionalLight> DirectionalLights, std::vector<PointLight> PointLights, std::vector<SpotLight> SpotLights, Vector3 AmbientLight, bool DebugMode)
{
	shader = Shader;
	directionalLights = DirectionalLights;
	pointLights = PointLights;
	spotLights = SpotLights;
	ambientLight = AmbientLight;

	if (DebugMode)
	{
		debugRender = true;
		SetupDebug();
	}
}

void LightManager::SetupDebug()
{
	//Assign shader
	Shaders shaders = GrabShader("resources/Shaders/UnlitColor.shader");
	debugShader = CreateShader(shaders.Vertex, shaders.Fragment);
	glUseProgram(debugShader);

	//Set scale
	transform.SetScale(Vector3(0.2f, 0.2f, 0.2f));

	//---Setup mesh---//
	//Gen and bind VAO
	glGenVertexArrays(1, &debugVAO);
	glBindVertexArray(debugVAO);

	//Generate buffers
	glGenBuffers(1, &debugVBO);
	glGenBuffers(1, &debugIBO);

	//Setup VBO
	glBindBuffer(GL_ARRAY_BUFFER, debugVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cubeVertices.size(), &cubeVertices[0], GL_STATIC_DRAW);

	//Setup IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, debugIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cubeIndices.size(), &cubeIndices[0], GL_STATIC_DRAW);

	//Setup vertex attributes
	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	//Texture Coord
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	//Normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));
}

void LightManager::UpdateLighting(unsigned int shad)
{
	//(if using same shader from before)
	if (shad == -1)
		shad = shader;
	else
		shader = shad;

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

void LightManager::DrawDebug(Matrix4 view, Matrix4 projection)
{
	//Use shader
	glUseProgram(debugShader);

	//Bind vao
	glBindVertexArray(debugVAO);

	//Render unlit cube for debugging
	//Point Lights
	for (int i = 0; i < pointLights.size(); i++)
	{
		//Set position of transform
		transform.SetPosition(pointLights[i].position);

		//Calc mat
		Matrix4 MVP = projection * view * transform.GetMatrix();

		//Pass color
		PassV3(debugShader, "uColor", pointLights[i].color);

		//Pass Matrix
		PassMat4(debugShader, "uMVPMatrix", MVP);

		//Draw
		glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, nullptr);
	}

	//Spot Lights
	for (int i = 0; i < spotLights.size(); i++)
	{
		//Set position of transform
		transform.SetPosition(spotLights[i].position);

		//Calc mat
		Matrix4 MVP = projection * view * transform.GetMatrix();

		//Pass color
		PassV3(debugShader, "uColor", spotLights[i].color);

		//Pass Matrix
		PassMat4(debugShader, "uMVPMatrix", MVP);

		//Draw
		glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, nullptr);
	}
}
