#pragma once

#include "Math\Math.h"

void PassFloat(int shader, const char* name, float value);
void PassInt(int shader, const char* name, int value);
void PassV3(int shader, const char* name, Vector3 &value);
void PassV4(int shader, const char* name, Vector4 &value);
void PassMat4(int shader, const char* name, Matrix4 &value);
