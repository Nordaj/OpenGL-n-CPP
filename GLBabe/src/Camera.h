#pragma once

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;
	bool lookAtGlobal;

	Camera();
	Camera(glm::vec3 Position, glm::vec3 LookAt, glm::vec3 Up, float Pov = 60, float Aspect = 1, float Near = 0.1f, float Far = 500);
	glm::mat4 GetView();
	glm::mat4 GetPerspective();

private: 
	float pov;
	float aspect;
	float near;
	float far;
};
