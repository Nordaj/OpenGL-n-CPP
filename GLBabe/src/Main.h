#pragma once

//Includes
#include <glew.h>
#include <glfw3.h>

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
Camera mainCamera;
Vector4 backgroundColor(0.02f, 0.02f, 0.02f, 1.0f);
float specularity = 1.3f;
double frameStartTime;
double deltaTime;
Vector3 camEuler;

double lastX;
double lastY;
double currentX;
double currentY;
Vector2 mouseIn;
float sensitivity = 200;

//Functions
int Setup();
void WindowSizeUpdate(GLFWwindow *win, int width, int height);
