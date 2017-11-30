#pragma once

class Transform 
{
public:
	Transform();
	Transform(glm::vec3 pos);
	glm::mat4 GetMatrix();
	void Translate(glm::vec3 translation);
	void Transform::SetPosition(glm::vec3 Position);
	void Rotate(glm::vec3 dir, float amount);
	void Scale(glm::vec3 sc);
	void SetScale(glm::vec3 sc);

private: 
	glm::vec3 position;
	glm::mat4 rotation;
	glm::vec3 scale;
};
