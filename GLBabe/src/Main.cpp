#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glew.h>
#include <glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>
#include <vector>

#include "Main.h"

int main()
{
	//Setup Game
	if (Setup()) return 0;

	//Handles vertex array, indicies, vbo, ibo, and vertex attributes
	int indLength = SetupCube();

	//Assign shader
	Shaders shaders = GrabShader("resources/Shaders/PhongMulti.shader");
	unsigned int shader = CreateShader(shaders.Vertex, shaders.Fragment); 
	glUseProgram(shader);

	//Light Stuff
	LightManager lightManager = LightManager(shader);
	lightManager.ambientLight = glm::vec3(0.05f, 0.05f, 0.05f);
	lightManager.directionalLights.push_back(DirectionalLight(glm::vec3(-1, -0.7f, 0), glm::vec3(1, 0.9f, 0.9f), 0.2f));
	lightManager.pointLights.push_back(PointLight(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 1));
	lightManager.pointLights.push_back(PointLight(glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0), 1));

	//Assign specularity
	PassFloat(shader, "uSpecularity", specularity);

	//Object's transform
	Transform cubes[] = {
		Transform(glm::vec3(-1, -1,  1)),
		Transform(glm::vec3(-1,  1,  1)),
		Transform(glm::vec3( 1,  1,  1)),
		Transform(glm::vec3( 1, -1,  1)),

		Transform(glm::vec3(-1, -1, -1)),
		Transform(glm::vec3(-1,  1, -1)),
		Transform(glm::vec3( 1,  1, -1)),
		Transform(glm::vec3( 1, -1, -1)),

		Transform(glm::vec3( 0, 0, -3))
	};

	//Rotate each cube individually
	cubes[0].Rotate(glm::vec3(0.2f, 0.9f, 0), 100);
	cubes[2].Rotate(glm::vec3(0.123f, 0.65f, 0.2f), 32);
	cubes[5].Rotate(glm::vec3(0.5f, 0.93f, 0), 164);
	cubes[6].Rotate(glm::vec3(0.1f, 0.9f, 0.8f), 63);
	cubes[8].Rotate(glm::vec3(1, 0, 0), 1);

	//Create camera
	mainCamera = Camera();
	mainCamera.position.z = 4;

	//Load Diffuse Tex
	glActiveTexture(GL_TEXTURE0);
	unsigned int diffuse = EasyLoad("resources/Diffuse.png", true, false);
	PassInt(shader, "uTex", 0);
	//Load Specular Tex
	glActiveTexture(GL_TEXTURE1);
	unsigned int specular = EasyLoad("resources/Specular.png", true, false);
	PassInt(shader, "uSpec", 1);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Get start time
		frameStartTime = glfwGetTime();

		//Clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Lighting
		lightManager.UpdateLighting(deltaTime);

		//Move cam for fun
		float xPos = 3 * sin(glfwGetTime() * 2);
		mainCamera.position.x = xPos;

		//Pass cam pos to shader
		PassV3(shader, "uCamPos", mainCamera.position);

		//Rotate cube[3]
		cubes[3].Rotate(glm::vec3(0.4f, 0.2f, 0.7f), 100 * deltaTime);

		for (int i = 0; i < sizeof(cubes) / sizeof(Transform); i++)
		{
			//MVP Matrix
			glm::mat4 model = cubes[i].GetMatrix();
			glm::mat4 view = mainCamera.GetView();
			glm::mat4 projection = mainCamera.GetPerspective();
			glm::mat4 MVPMatrix = projection * view * model;

			//Give MVP to shader
			PassMat4(shader, "uMVPMatrix", MVPMatrix);

			//Give model matrix
			PassMat4(shader, "uModel", model);

			//DRAW
			glDrawElements(GL_TRIANGLES, indLength, GL_UNSIGNED_INT, nullptr);
		}

		//Swap buffers
		glfwSwapBuffers(window);

		//Poll events
		glfwPollEvents();

		//Get delta time
		deltaTime = glfwGetTime() - frameStartTime;
	}

	//End
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}

int Setup()
{
	//Initialize glfw
	glfwInit();

	//Create window
	window = glfwCreateWindow(WIDTH, HEIGHT, WINDOWNAME, NULL, NULL);

	//Set window current
	glfwMakeContextCurrent(window);

	//Debug version
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	//Init glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init" << std::endl;
		std::cin.get();
		return 0;
	}

	//Set size callback
	glfwSetWindowSizeCallback(window, WindowSizeUpdate);

	//Clear color
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//Wireframe mode
	if (WIREFRAMEMODE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Enable/Disable vsync
	glfwSwapInterval(VSYNC);

	//Return
	return 0;
}

void WindowSizeUpdate(GLFWwindow *win, int width, int height)
{
	glViewport(0, 0, width, height);
	mainCamera.UpdateAspect((float) width / (float) height);
}
