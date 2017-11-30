#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Shaders {
	std::string Vertex;
	std::string Fragment;

	Shaders(std::string vert, std::string frag)
		:Vertex(vert), Fragment(frag)
	{
	}
};

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