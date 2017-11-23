#pragma once

int SetupCube()
{
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

	return sizeof(ind) / sizeof(unsigned int);
}