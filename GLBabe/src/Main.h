#pragma once

//Includes
#include <glew.h>
#include <glfw3.h>
#include <glm\glm.hpp>

#include "Camera.h"

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
glm::vec4 backgroundColor(0.02f, 0.02f, 0.02f, 1.0f);
float specularity = 1.3f;
double frameStartTime;
double deltaTime;
float camSpeed = 10;
float camRotSpeed = 2;
double cursorX;
double cursorY;
double lastCursorX;
double lastCursorY;

//Functions
int Setup();
void WindowSizeUpdate(GLFWwindow *win, int width, int height);
