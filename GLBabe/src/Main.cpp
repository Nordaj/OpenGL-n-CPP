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

int main()
{
	//Setup Game
	if (Setup()) return 0;

	//Clear color
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

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

	//Rectangle
	float points[] = {
		//Positions           //Colors           //Tex coords
		-0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 
		 0.5f, -0.5f,  0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f
	};

	//Cube
	float pts[] = {
		//Positions           //Colors           //Tex coord  //Normals
		//Front
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f, //0
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f, //1
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f, //2
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f, //3

		//Back
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f, //4
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f, //5
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f, //6
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f, //7

		//Right
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f, //8
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f, //9
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f, //10
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f, //11

		//Left
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f, //12
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f, //13
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f, //14
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f, //15

		//Top
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f, //16
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f, //17
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f, //18
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f, //19

		//Bottom
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f, //20
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f, //21
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f, //22
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f  //23
	};

	//Elements to use for triangles
	unsigned int indices[] = {
		0, 1, 2, 
		2, 3, 0
	};

	//Elements to use for cube
	unsigned int ind[] = {
		//Front
		0, 1, 2,
		2, 3, 0,

		//Back
		4, 5, 6,
		6, 7, 4,

		//Right
		8, 9, 10,
		10, 11, 8,

		//Left
		12, 13, 14,
		14, 15, 12,

		//Top
		16, 17, 18,
		18, 19, 16,

		//Bottom
		20, 21, 22,
		22, 23, 20,
	};
	
	//Crate vertex buffer (generate buffer, bind buffer, give desc)
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pts), &pts, GL_STATIC_DRAW);
	
	//Position attrubute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, 0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*) (sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	//Texture coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	//Texture coordinate attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);

	//Create index buffer object (generate buffer, bind buffer, give desc)
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), &ind, GL_STATIC_DRAW);

	//Get shaders
	Shaders shaders = GrabShader("resources/Shaders/Unlit.shader");

	//Create shaders
	unsigned int shader = CreateShader(shaders.Vertex, shaders.Fragment); 
	glUseProgram(shader);

	//Assign uniform ambient color
	int col = glGetUniformLocation(shader, "ambient");
	glUniform3fv(col, 1, &ambientLight.x);

	//Give the pos of my light
	int c = glGetUniformLocation(shader, "lightPos");
	glUniform3fv(c, 1, &lightPos.x);

	//Wireframe mode
	if (WIREFRAMEMODE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//Object's transform
	Transform cubes[] = {
		Transform(glm::vec3(-1, -1,  0)),
		Transform(glm::vec3(-1,  1,  0)),
		Transform(glm::vec3( 1,  1,  0)),
		Transform(glm::vec3( 1, -1,  0)),

		Transform(glm::vec3(-1, -1, -2)),
		Transform(glm::vec3(-1,  1, -2)),
		Transform(glm::vec3( 1,  1, -2)),
		Transform(glm::vec3( 1, -1, -2))
	};

	Transform transform;
	transform.Rotate(glm::vec3(1, 0, 1), 45);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Move cam for fun
		float xPos = 3 * sin(glfwGetTime() * 2);
		camPos.x = xPos;

		for (int i = 0; i < sizeof(cubes) / sizeof(Transform); i++)
		{
			//Rotate cubes
			cubes[i].Rotate(glm::vec3(1, 1, 0), 0.6f);

			//Model matrix
			glm::mat4 model = cubes[i].GetMatrix();

			//Give model matrix
			int mo = glGetUniformLocation(shader, "model");
			glUniformMatrix4fv(mo, 1, GL_FALSE, glm::value_ptr(model));

			//View matrix
			glm::mat4 view = glm::mat4(1.0f);
			//view = glm::lookAt(camPos, camPos + camFront, camUp);
			view = glm::lookAt(camPos, glm::vec3(0.0f, 0.0f, -3.0f), camUp);
			//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			//Projection matrix
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(60.0f), (float)(WIDTH / HEIGHT), 0.1f, 100.0f);

			//MVPMatrix
			glm::mat4 MVPMatrix = projection * view * model;

			//Give matrices to shader
			int mat = glGetUniformLocation(shader, "MVPMatrix");
			glUniformMatrix4fv(mat, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

			//Draw the triangle
			glDrawElements(GL_TRIANGLES, sizeof(ind) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
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
}

static Shaders GrabShader(std::string path)
{
	//Get shader, init vars
	std::ifstream stream(path);
	int type = 0; ///0=unknown, 1=vert, 2=frag
	std::string ln;
	std::stringstream vert, frag;

	//Search shaders, add to stringstream
	while (getline(stream, ln))
	{
		if (ln.find("#shader") != std::string::npos)
		{
			if (ln.find("vertex") != std::string::npos)
				type = 1;
			else if (ln.find("fragment") != std::string::npos)
				type = 2;
		}
		else if (type == 1)///vert
		{
			vert << ln << std::endl;
		}
		else if (type == 2)///frag
		{
			frag << ln << std::endl;
		}
	}

	//Give em back
	return Shaders(vert.str(), frag.str());
}

static unsigned int CompileShader(const std::string src, int type)
{
	//Create shader, put into char, give source, compile
	unsigned int id = glCreateShader(type);
	const char *charSrc = src.c_str();
	glShaderSource(id, 1, &charSrc, nullptr);
	glCompileShader(id);

	//Errors
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) //Something failed
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)alloca(length * sizeof(char));//To create a char* with variable length
		glGetShaderInfoLog(id, length, &length, msg);

		std::cout << "Error compiling shader: " << std::endl;
		std::cout << msg << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string &vertShader, const std::string &fragShader)
{
	//Create shader program
	unsigned int p = glCreateProgram();

	//Compile shaders
	unsigned int vert = CompileShader(vertShader, GL_VERTEX_SHADER);
	unsigned int frag = CompileShader(fragShader, GL_FRAGMENT_SHADER);

	//Give shaders to opengl
	glAttachShader(p, vert);
	glAttachShader(p, frag);
	glLinkProgram(p);
	glValidateProgram(p);

	//Delete
	glDeleteShader(vert);
	glDeleteShader(frag);

	return p;
}
