#pragma once

class Transform {
public:
	Transform();
	Transform(glm::vec3 pos);
	glm::mat4 GetMatrix();
	void Translate(glm::vec3 translation);
	void Rotate(glm::vec3 dir, float amount);
	void Scale(glm::vec3 scale);

private: 
	glm::vec3 position;
	glm::mat4 rotation;
	glm::vec3 scale;
};
