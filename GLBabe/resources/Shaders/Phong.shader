#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

out vec3 iCol;
out vec2 iTextureCoord;
out vec3 iNormal;
out vec3 iFragPos;

uniform mat4 uMVPMatrix;
uniform mat4 uModel;

void main()
{
	gl_Position = uMVPMatrix * position;
	iCol = color;
	iTextureCoord = texCoord;

	//TODO: calculate on cpu instead
	iNormal = mat3(transpose(inverse(uModel))) * normal;
	iFragPos = vec3(uModel * position);
}

#shader fragment
#version 330 core

out vec4 color;

in vec3 iCol;
in vec2 iTextureCoord;
in vec3 iNormal;
in vec3 iFragPos;

uniform sampler2D uTex;
uniform sampler2D uSpec;

uniform vec3 uAmbient;

uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform float uLightIntensity;

uniform vec3 uDLightDirection;
uniform vec3 uDLightColor;
uniform float uDLightIntensity;

uniform vec3 uCamPos;
uniform float uSpecularity;

float Attenuation(float constant, float lin, float quadratic, float distance);

void main()
{
	//-------------Directional Light-----------------
	//Use for all
	vec3 normal = normalize(iNormal);

	//Ambient
	vec3 ambCol = uAmbient;

	//Direction
	vec3 dir = normalize(-uDLightDirection);
	float dirIntensity = dot(dir, normal);
	if (dirIntensity < 0) dirIntensity = 0;
	vec3 dirCol = uDLightColor * (dirIntensity * uDLightIntensity);

	//-------------Point Light----------------- 
	float distance = length(uLightPos - iFragPos) / uLightIntensity;
	vec3 ptDir = normalize(uLightPos - iFragPos);
	float attenuation = Attenuation(1.0, 1, 2, distance);
	float dotResult = dot(ptDir, normal);
	vec3 pointLightCol = uLightColor * (attenuation * dotResult);

	//Calc result
	vec4 result = vec4(pointLightCol + dirCol, 1.0);

	//Output
	color = result;
}

float Attenuation(float constant, float lin, float quadratic, float distance)
{
	return 1.0 / (constant + lin * distance + quadratic * (distance * distance));
}