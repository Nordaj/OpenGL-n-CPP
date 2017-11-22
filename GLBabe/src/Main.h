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
glm::vec3 ambientLight = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 lightPos = glm::vec3(0, 0, 0);
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Functions
int Setup();
static Shaders GrabShader(std::string path);
static unsigned int CompileShader(const std::string src, int type);
static unsigned int CreateShader(const std::string &vertShader, const std::string &fragShader);
