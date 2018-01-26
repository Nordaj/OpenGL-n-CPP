//Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glew.h>
#include <glfw3.h>
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
#include "Object.h"
#include "LightManager.h"
#include "HardCodedMeshes.h"
#include "Math\Math.h"

#include "Main.h"

int main()
{
	//MATH

	Matrix3 mat = Matrix3::FromEuler(Vector3(5, 45, 45));
	std::cout << mat << std::endl;

	Matrix3 mat2 = Matrix3();
	mat2.Rotate(Vector3(1, 0, 0), 5);
	mat2.Rotate(Vector3(0, 1, 0), 45);
	mat2.Rotate(Vector3(0, 0, 1), 45);
	std::cout << mat2 << std::endl;

	Quaternion q1 = mat.ToQuaternion();
	Quaternion q2 = mat2.ToQuaternion();
	std::cout << q1 << std::endl;
	std::cout << q2 << std::endl;

	//END MATH

	//std::cin.get();
	//std::cin.get();
	//return 0;

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
	lightManager.ambientLight = Vector3(0.1f, 0.1f, 0.1f);
	lightManager.directionalLights.push_back(DirectionalLight(Vector3(-1, -0.7f, 0), Vector3(1, 0.9f, 0.9f), 0.2f));
	lightManager.pointLights.push_back(PointLight(Vector3(0, 0, 0), Vector3(0, 1, 0), 1));
	lightManager.pointLights.push_back(PointLight(Vector3(-2, 0, 0), Vector3(1, 0, 0), 1));
	lightManager.spotLights.push_back(SpotLight(Vector3(-1, 0, 0), Vector3(2, -1, -1), Vector3(0, 0, 1), 3, cos(Radians(10.0f))));
	//Spot lights are broken, recently found a problem (look at ground, should see a yellowish circle)

	//Create camera
	mainCamera = Camera();
	mainCamera.position = Vector3(0, 0, 4);

	//Create objects
	Object models[] = {
		//cubes
		Object(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(Vector3(-1, -1,  1))),
		Object(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(Vector3(-1,  1,  1))),
		Object(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(Vector3( 1,  1,  1))),
		Object(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(Vector3( 1, -1,  1))),
		
		Object(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(Vector3(-1, -1, -1))),
		Object(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(Vector3(-1,  1, -1))),
		Object(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(Vector3( 1,  1, -1))),
		Object(Mesh(cubeVertices, cubeIndices, diffuse, specular, shader), 1, shader, Transform(Vector3( 1, -1, -1))),
		
		//pyramid
		Object(Mesh(pyramidVertices, pyramidIndices, diffuse, specular, shader), 1, shader, Transform(Vector3(0, 0, -3))),

		//quad
		Object(Mesh(quadVertices, quadIndices, ground, specular, shader), 0, shader, Transform(Vector3(0, -2, 0)))
	};

	//Set ground scale
	models[9].transform.SetScale(Vector3(4, 1, 4));

	//Set default rotations TODO: set with euler for readability
	models[0].transform.Rotate(Vector3(20, 90, 0));
	models[2].transform.Rotate(Vector3(23, 65, 38));
	models[5].transform.Rotate(Vector3(0, 0, 45));
	models[6].transform.Rotate(Vector3(50, 10, 0));

	//Lock Cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Get start time
		frameStartTime = glfwGetTime();

		//Clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Move cam for fun
		//float xPos = (float) sin(glfwGetTime() * 2);
		//mainCamera.position.x = xPos;

		//Camera Controls
		glfwGetCursorPos(window, &currentX, &currentY);
		mouseIn = Vector2(currentX - lastX, currentY - lastY);
		glfwGetCursorPos(window, &lastX, &lastY);

		//Cheap way to do it, i just keep track of euler instead of conversion. need to make matrix conversion before i make quat conversion
		camEuler += Vector3(mouseIn.y * (float)deltaTime * sensitivity, mouseIn.x * (float)deltaTime * sensitivity, 0);
		mainCamera.rotation = Quaternion::FromEuler(camEuler);

		//Rotate cube and pyramid
		models[3].transform.Rotate(Vector3(40, 0, 0) * (float) deltaTime);
		models[8].transform.Rotate(Vector3(100, 100, 0) * (float) deltaTime);

		//Calculate view/perspectives
		Matrix4 viewMat = mainCamera.GetView();
		Matrix4 perspectiveMat = mainCamera.GetProjection();

		//Decide if first model (with specific shader)
		bool first = true;

		//Draw models
		for (int i = 0; i < sizeof(models) / sizeof(Object); i++)
		{
			models[i].Update((float) deltaTime);

			models[i].Render(viewMat, perspectiveMat, mainCamera.position, lightManager, first);

			first = false;
		}

		//Draw debug lights
		lightManager.DrawDebug(viewMat, perspectiveMat);

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
