//Includes
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
#include "Transform.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Shader.h"
#include "UniformHandler.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "LightManager.h"
#include "HardCodedMeshes.h"

#include "Main.h"

int main()
{
	//Setup Game
	if (Setup()) return 0;

	//Assign shader
	Shaders shaders = GrabShader("resources/Shaders/PhongMulti.shader");
	unsigned int shader = CreateShader(shaders.Vertex, shaders.Fragment);
	glUseProgram(shader);

	//Load Diffuse Tex
	glActiveTexture(GL_TEXTURE0);
	unsigned int diffuse = EasyLoad("resources/Diffuse.png", true, false);

	//Load Specular Tex
	glActiveTexture(GL_TEXTURE1);
	unsigned int specular = EasyLoad("resources/Specular.png", true, false);

	//Load Ground Tex
	glActiveTexture(GL_TEXTURE0);
	unsigned int ground = EasyLoad("resources/GroundDiffuse.png", true, false);

	//Light Stuff
	LightManager lightManager = LightManager(shader, DEBUGLIGHTS);
	lightManager.ambientLight = glm::vec3(0.05f, 0.05f, 0.05f);
	lightManager.directionalLights.push_back(DirectionalLight(glm::vec3(-1, -0.7f, 0), glm::vec3(1, 0.9f, 0.9f), 0.2f));
	lightManager.pointLights.push_back(PointLight(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 1));
	lightManager.pointLights.push_back(PointLight(glm::vec3(-2, 0, 0), glm::vec3(1, 0, 0), 1));
	lightManager.spotLights.push_back(SpotLight(glm::vec3(-1, 0, 0), glm::vec3(2, -1, -1), glm::vec3(0, 0, 1), 3, glm::cos(glm::radians(10.0f))));
	//Spot lights are broken, recently found a problem (look at ground, should see a yellowish circle)

	//Create camera
	mainCamera = Camera();
	mainCamera.position.z = 4;

	//Create objects
	Model models[] = {
		//cubes
		Model(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(glm::vec3(-1, -1,  1))),
		Model(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(glm::vec3(-1,  1,  1))),
		Model(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(glm::vec3( 1,  1,  1))),
		Model(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(glm::vec3( 1, -1,  1))),
		
		Model(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(glm::vec3(-1, -1, -1))),
		Model(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(glm::vec3(-1,  1, -1))),
		Model(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(glm::vec3( 1,  1, -1))),
		Model(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(glm::vec3( 1, -1, -1))),
		
		Model(Mesh(pyramidVertices, pyramidIndices, diffuse, specular, shader), 1, shader, Transform(glm::vec3(0, 0, -3))),

		//quad
		Model(Mesh(quadVertices, quadIndices, ground, specular, shader), 0, shader, Transform(glm::vec3(0, -2, 0)))
	};

	//Set ground scale
	models[9].transform.SetScale(glm::vec3(4, 1, 4));

	//Set default rotations
	models[0].transform.Rotate(glm::vec3(0.2f, 0.9f, 0), 100);
	models[2].transform.Rotate(glm::vec3(0.123f, 0.65f, 0.2f), 32);
	models[5].transform.Rotate(glm::vec3(0.5f, 0.93f, 0), 164);
	models[6].transform.Rotate(glm::vec3(0.1f, 0.9f, 0.8f), 63);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Get start time
		frameStartTime = glfwGetTime();

		//Clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Move cam for fun
		float xPos = 5 * (float) sin(glfwGetTime() * 2);
		mainCamera.position.x = xPos;

		models[3].transform.Rotate(glm::vec3(0.4f, 0.2f, 0.7f), 100 * (float) deltaTime);
		models[8].transform.Rotate(glm::vec3(1, 1, 0), 100 * (float) deltaTime);

		//Draw models
		for (int i = 0; i < sizeof(models) / sizeof(Model); i++) 
		{
			models[i].Update((float) deltaTime);

			models[i].Render(mainCamera.GetView(), mainCamera.GetPerspective(), mainCamera.position, lightManager);
		}

		//Draw debug lights
		lightManager.DrawDebug(mainCamera.GetView(), mainCamera.GetPerspective());

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
