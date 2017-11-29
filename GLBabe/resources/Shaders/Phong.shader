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

struct PointLight {
	vec3 position;
	vec3 color;
	float intensity;
};

struct DirectionalLight {
	vec3 direction;
	vec3 color;
	float intensity;
};

uniform sampler2D uTex;
uniform sampler2D uSpec;

uniform vec3 uAmbient;

uniform PointLight pointLight;

//uniform vec3 uDLightDirection;
//uniform vec3 uDLightColor;
//uniform float uDLightIntensity;
uniform DirectionalLight directionalLight;

uniform vec3 uCamPos;
uniform float uSpecularity;

float Attenuation(float constant, float lin, float quadratic, float distance);

void main()
{
	//-------------Use for all-----------------------
	//Get normalized normal
	vec3 normal = normalize(iNormal);
	//Ambient
	vec3 ambCol = uAmbient * texture(uTex, iTextureCoord).rgb;
	//View direction
	vec3 viewDir = normalize(uCamPos - iFragPos);

	//-------------Directional Light-----------------
	//Diffuse
	vec3 DL_dir = normalize(-directionalLight.direction);
	float DL_dirIntensity = dot(DL_dir, normal);
	if (DL_dirIntensity < 0) DL_dirIntensity = 0;
	vec3 DL_difCol = directionalLight.color * (DL_dirIntensity * directionalLight.intensity);
	//Specular
	vec3 DL_refDir = reflect(-DL_dir, normal);
	float DL_specIntensity = dot(viewDir, DL_refDir);
	if (DL_specIntensity < 0) DL_specIntensity = 0;
	DL_specIntensity = pow(DL_specIntensity, 32);
	DL_specIntensity *= uSpecularity * directionalLight.intensity;
	vec3 DL_specCol = DL_specIntensity * texture(uSpec, iTextureCoord).rgb * directionalLight.color;
	//Output
	vec3 dirCol = (DL_difCol + DL_specCol) * texture(uTex, iTextureCoord).rgb;

	//-------------Point Light-----------------------
	//Diffuse
	float PL_distance = length(pointLight.position - iFragPos) / pointLight.intensity;
	vec3 PL_ptDir = normalize(pointLight.position - iFragPos);
	float PL_attenuation = Attenuation(1.0, 1, 2, PL_distance);
	float PL_dotResult = dot(PL_ptDir, normal);
	vec3 PL_difColor = pointLight.color * (PL_attenuation * PL_dotResult);
	//Specular
	vec3 PL_refDir = reflect(-PL_ptDir, viewDir);
	float PL_specIntensity = dot(viewDir, PL_refDir);
	if (PL_specIntensity < 0) PL_specIntensity = 0;
	PL_specIntensity = pow(PL_specIntensity, 32);
	PL_specIntensity *= uSpecularity * PL_attenuation;
	vec3 PL_specColor = PL_specIntensity * texture(uSpec, iTextureCoord).rgb * pointLight.color;
	//Output
	vec3 pointLightCol = (PL_difColor + PL_specColor) * texture(uTex, iTextureCoord).rgb;

	//-------------Calc result-----------------------
	vec4 result = vec4(pointLightCol + dirCol + ambCol, 1.0);

	//-------------Output----------------------------
	color = result;
}

float Attenuation(float constant, float lin, float quadratic, float distance)
{
	return 1.0 / (constant + lin * distance + quadratic * (distance * distance));
}
