#pragma once

//Includes
#include <glm\glm.hpp>

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 eulerAngles;

	Camera();
	Camera(glm::vec3 Position, float Pov = 60, float Aspect = 1, float Near = 0.1f, float Far = 500);
	//(F means first, only engine calls it first time so i can set to true and the rest each frame doesnt need to calculate but just pass)
	glm::mat4 GetView();
	glm::mat4 GetProjection();
	void UpdateAspect(float aspect);
	void RelativeTranslate(glm::vec3 translation);

private: 
	bool first;
	float pov;
	float aspect;
	float near;
	float far;
	glm::mat4 view;
	glm::mat4 projection;
};
