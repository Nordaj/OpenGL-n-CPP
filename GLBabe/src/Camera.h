#pragma once

//Includes
#include <glm\glm.hpp>

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;
	bool lookAtGlobal;

	Camera();
	Camera(glm::vec3 Position, glm::vec3 LookAt, glm::vec3 Up, float Pov = 60, float Aspect = 1, float Near = 0.1f, float Far = 500);
	//(F means first, only engine calls it first time so i can set to true and the rest each frame doesnt need to calculate but just pass)
	glm::mat4 GetView();
	glm::mat4 GetPerspective();
	void UpdateAspect(float aspect);

private: 
	bool first;
	float pov;
	float aspect;
	float near;
	float far;
	glm::mat4 view;
	glm::mat4 projection;
};
