#pragma once

//Includes
#include "Transform.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Cube.h"
#include "Shader.h"
#include "UniformHandler.h"
#include "Texture.h"
#include "Camera.h"

//Defines
#define WIREFRAMEMODE false
#define WIDTH 500
#define HEIGHT 500
#define WINDOWNAME "Hey"

//Variables
GLFWwindow *window;
Camera mainCamera; //TODO find solution
glm::vec4 backgroundColor(0.05f, 0.05f, 0.05f, 1.0f);
glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);
float specularity = 0.2f;

//Functions
int Setup();
void WindowSizeUpdate(GLFWwindow *win, int width, int height);
