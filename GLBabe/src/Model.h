#pragma once

#include <vector>
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Transform.h"
#include "LightManager.h"

class Model {
public:
	Model(Mesh m, float Specularity, unsigned int Shader, Transform tran = Transform());
	Model(std::vector<float> Vertices, std::vector<unsigned int> Indices, unsigned int Diffuse, unsigned int Specular, unsigned int Shader, float Specularity, Transform tran = Transform());
	virtual void Update(float deltaTime);
	void Render(glm::mat4 view, glm::mat4 projection, glm::vec3 camPos, LightManager lightManager);

	Transform transform;

private:
	Mesh mesh;
	float specularity;
	unsigned int shader;

};
