#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glew.h>
#include <glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <vector>

#include "Mesh.h"
#include "Transform.h"
#include "UniformHandler.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "LightManager.h"

#include "Model.h"

Model::Model(Mesh m, float Specularity, unsigned int Shader, Transform tran)
	:mesh(m), specularity(Specularity), shader(Shader), transform(tran) { }

Model::Model(std::vector<float> Vertices, std::vector<unsigned int> Indices, unsigned int Diffuse, unsigned int Specular, unsigned int Shader, float Specularity, Transform tran)
	:mesh(Mesh(Vertices, Indices, Diffuse, Specular, Shader)), specularity(Specularity), transform(tran), shader(Shader) { }

void Model::Update(float deltaTime)
{

}

void Model::Render(glm::mat4 view, glm::mat4 projection, glm::vec3 camPos, LightManager *lightManager, bool first)
{
	//Calculate matrices
	glm::mat4 model = transform.GetMatrix();
	glm::mat4 MVP = projection * view * model;

	if (first)
	{
		//Use shader
		glUseProgram(shader);

		//Update Lighting
		lightManager->UpdateLighting(shader);
	}

	//Pass uniforms
	PassFloat(shader, "uSpecularity", specularity);
	PassMat4(shader, "uMVPMatrix", MVP);
	PassMat4(shader, "uModel", model);
	PassV3(shader, "uCamPos", camPos);

	//Render!
	mesh.Draw();
}
