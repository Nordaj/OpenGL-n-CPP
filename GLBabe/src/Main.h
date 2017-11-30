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
#include "LightManager.h"

//Defines
#define WIREFRAMEMODE false
#define VSYNC false
#define WIDTH 500
#define HEIGHT 500
#define WINDOWNAME "Hey"
#define DEBUGLIGHTS true

//Variables
GLFWwindow *window;
Camera mainCamera; //TODO find solution
glm::vec4 backgroundColor(0.05f, 0.05f, 0.05f, 1.0f);
float specularity = 1.3f;
double frameStartTime;
double deltaTime;

//Functions
int Setup();
void WindowSizeUpdate(GLFWwindow *win, int width, int height);
