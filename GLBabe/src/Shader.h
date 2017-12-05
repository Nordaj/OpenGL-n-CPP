#pragma once

#include <iostream>
#include <string>

struct Shaders {
	std::string Vertex;
	std::string Fragment;

	Shaders(std::string vert, std::string frag)
		:Vertex(vert), Fragment(frag)
	{ }
};

Shaders GrabShader(std::string path);

unsigned int CompileShader(const std::string src, int type);

unsigned int CreateShader(const std::string &vertShader, const std::string &fragShader);