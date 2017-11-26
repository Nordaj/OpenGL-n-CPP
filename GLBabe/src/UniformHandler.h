#pragma once

void PassFloat(int shader, const char* name, float value);
void PassInt(int shader, const char* name, int value);
void PassV3(int shader, const char* name, glm::vec3 value);
void PassV4(int shader, const char* name, glm::vec4 value);
void PassMat4(int shader, const char* name, glm::mat4 value);
