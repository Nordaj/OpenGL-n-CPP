#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Main.h"
#include "Transform.h"
#include "Light.h"
#include "Cube.h"
#include "Shader.h"
#include "Camera.h"
#include "UniformHandler.h"

int main()
{
	//Setup Game
	if (Setup()) return 0;

	//Load texture
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("resources/Jordy.jpg", &width, &height, &channels, 0);

	//Bind texture
	unsigned int tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	//Give texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Free stbi memory
	stbi_image_free(data);

	//Handles vertex array, indicies, vbo, ibo, and vertex attributes
	int indLength = SetupCube();

	//Assign shader
	Shaders shaders = GrabShader("resources/Shaders/Phong.shader");
	unsigned int shader = CreateShader(shaders.Vertex, shaders.Fragment); 
	glUseProgram(shader);

	//Assign ambient color
	PassV3(shader, "uAmbient", ambientLight);

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
		Transform(glm::vec3( 1, -1, -1))
	};

	//Light stuff
	Light light = Light(glm::vec3(0, 0, 0), glm::vec3(1, 0, 1), 1);
	light.PassPosition(shader, "uLightPos");
	light.PassColor(shader, "uLightColor");
	light.PassIntensity(shader, "uLightIntensity");

	//Create camera
	Camera camera = Camera();
	camera.position.z = 4;

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Move cam for fun
		float xPos = 3 * sin(glfwGetTime() * 2);
		camera.position.x = xPos;

		//Pass cam pos to shader
		PassV3(shader, "uCamPos", camera.position);

		for (int i = 0; i < sizeof(cubes) / sizeof(Transform); i++)
		{
			//Rotate cubes
			cubes[i].Rotate(glm::vec3(1, 1, 0), 0.6f);

			//MVP Matrix
			glm::mat4 model = cubes[i].GetMatrix();
			glm::mat4 view = camera.GetView();
			glm::mat4 projection = camera.GetPerspective();
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

	//Clear color
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//Wireframe mode
	if (WIREFRAMEMODE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Return
	return 0;
}
