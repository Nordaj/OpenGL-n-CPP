#pragma once

#include <vector>
#include "Mesh.h"
#include "Transform.h"
#include "LightManager.h"
#include "Math\Math.h"

class Object {
public:
	Object(Mesh m, float Specularity, unsigned int Shader, Transform tran = Transform());
	Object(std::vector<float> Vertices, std::vector<unsigned int> Indices, unsigned int Diffuse, unsigned int Specular, unsigned int Shader, float Specularity, Transform tran = Transform());
	virtual void Update(float deltaTime);
	//First helps decide if i need to update lighting, (very important to not ignore)
	void Render(Matrix4 &view, Matrix4 &projection, Vector3 &camPos, LightManager &lightManager, bool first = true);

	Transform transform;

private:
	Mesh mesh;
	float specularity;
	unsigned int shader;
};
