#pragma once

//Defines
#define WIREFRAMEMODE false
#define WIDTH 500
#define HEIGHT 500
#define WINDOWNAME "Hey"

//Structures
struct Shaders {
	std::string Vertex;
	std::string Fragment;

	Shaders(std::string vert, std::string frag)
		:Vertex(vert), Fragment(frag) { }
};

//Variables
GLFWwindow *window;
glm::vec4 backgroundColor(0.05f, 0.05f, 0.05f, 1.0f);
glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);
float specularity = 0.2f;

//Functions
int Setup();
