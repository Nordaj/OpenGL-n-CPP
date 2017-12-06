#pragma once

#include <vector>
#include <glm\glm.hpp>

class Mesh {
public:
	Mesh(std::vector<float> Vertices, std::vector<unsigned int> Indices, unsigned int Diffuse, unsigned int Specular, unsigned int Shader);
	void Draw();

private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int diffuse;
	unsigned int specular;
	unsigned int shader;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;
};
