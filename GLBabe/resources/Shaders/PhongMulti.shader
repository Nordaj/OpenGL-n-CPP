#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 iTextureCoord;
out vec3 iNormal;
out vec3 iFragPos;

uniform mat4 uMVPMatrix;
uniform mat4 uModel;

void main()
{
	gl_Position = uMVPMatrix * position;
	iTextureCoord = texCoord;

	//TODO: calculate on cpu instead
	iNormal = mat3(transpose(inverse(uModel))) * normal;
	iFragPos = vec3(uModel * position);
}

#shader fragment
#version 330 core

out vec4 color;

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

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 color;
	float intensity;
	float cutoff;
};

uniform sampler2D uTex;
uniform sampler2D uSpec;

uniform vec3 uAmbient;

//I pulled these max numbers for lights out of my ass, feel free to change them
uniform PointLight pointLight[8];
uniform DirectionalLight directionalLight[4];
uniform SpotLight spotLight[8];

uniform vec3 uCamPos;
uniform float uSpecularity;

float Attenuation(float constant, float lin, float quadratic, float distance);
vec3 CalcDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight pLight, vec3 normal, vec3 viewDir, vec3 fragPos);
vec3 CalcSpotLight(SpotLight sLight, vec3 normal, vec3 viewDir, vec3 fragPos);

/*
void main()
{
	//-------------Use for all-----------------------
	//Get normalized normal
	vec3 normal = normalize(iNormal);
	//Ambient
	vec3 ambCol = uAmbient * texture(uTex, iTextureCoord).rgb;
	//View direction
	vec3 viewDir = normalize(uCamPos - iFragPos);

	vec3 dirCol = CalcDirectionalLight(directionalLight, normal, viewDir);
	vec3 pointLightCol = CalcPointLight(pointLight, normal, viewDir, iFragPos);

	//-------------Calc result-----------------------
	vec4 result = vec4(pointLightCol + dirCol + ambCol, 1.0);

	//-------------Output----------------------------
	color = result;
}
*/

void main()
{
	//-------------Use for all-----------------------
	//Get normalized normal
	vec3 normal = normalize(iNormal);
	//Ambient
	vec3 ambCol = uAmbient * texture(uTex, iTextureCoord).rgb;
	//View direction
	vec3 viewDir = normalize(uCamPos - iFragPos);

	//-------------Calculate Directional-------------
	vec3 dirCol = vec3(0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		if (directionalLight[i].intensity != 0)
			dirCol += CalcDirectionalLight(directionalLight[i], normal, viewDir);
	}

	//-------------Calculate Directional-------------
	vec3 pointLightCol = vec3(0, 0, 0);
	for (int i = 0; i < 8; i++)
	{
		if (pointLight[i].intensity != 0)
			pointLightCol += CalcPointLight(pointLight[i], normal, viewDir, iFragPos);
	}

	//-------------Spot Light------------------------
	vec3 spotLightCol = vec3(0, 0, 0);
	for (int i = 0; i < 8; i++)
	{
		if (spotLight[i].intensity != 0)
			pointLightCol += CalcSpotLight(spotLight[i], normal, viewDir, iFragPos);
	}

	//-------------Calc Result-----------------------
	vec4 result = vec4(pointLightCol + dirCol + spotLightCol + ambCol, 1.0);

	//-------------Output----------------------------
	//color = texture(uSpec, iTextureCoord);
	color = result;
}

float Attenuation(float constant, float lin, float quadratic, float distance)
{
	return 1.0 / (constant + lin * distance + quadratic * (distance * distance));
}

vec3 CalcDirectionalLight(DirectionalLight dLight, vec3 normal, vec3 viewDir)
{
	//Diffuse
	vec3 direction = normalize(-dLight.direction);
	float diffuseIntensity = dot(normal, direction) * dLight.intensity;
	if (diffuseIntensity < 0) diffuseIntensity = 0;
	vec3 diffuseColor = dLight.color * diffuseIntensity * texture(uTex, iTextureCoord).rgb;

	//Specular
	vec3 reflectionDirection = reflect(-direction, normal);
	float specIntensity = dot(viewDir, reflectionDirection);
	if (specIntensity < 0) specIntensity = 0;
	specIntensity = pow(specIntensity, 32);
	specIntensity *= uSpecularity * dLight.intensity;
	vec3 specColor = specIntensity * texture(uSpec, iTextureCoord).rgb * dLight.color;

	//Return
	return specColor + diffuseColor;
}

vec3 CalcPointLight(PointLight pLight, vec3 normal, vec3 viewDir, vec3 fragPos)
{
	//Diffuse
	float distance = length(pLight.position - fragPos) / pLight.intensity;
	vec3 direction = normalize(pLight.position - fragPos);
	float attenuation = Attenuation(1.0, 1, 2, distance);
	float dotResult = dot(direction, normal);
	vec3 diffuseColor = pLight.color * (attenuation * dotResult) * texture(uTex, iTextureCoord).rgb;

	//Specular
	vec3 reflectionDirection = reflect(-direction, viewDir);
	float specIntensity = dot(viewDir, reflectionDirection);
	if (specIntensity < 0) specIntensity = 0;
	specIntensity = pow(specIntensity, 32);
	specIntensity *= uSpecularity * attenuation;
	vec3 specColor = specIntensity * texture(uSpec, iTextureCoord).rgb * pLight.color;

	//Return
	return specColor + diffuseColor;
}

vec3 CalcSpotLight(SpotLight sLight, vec3 normal, vec3 viewDir, vec3 fragPos)
{
	//difference is normally "theta" but im not good at mathy stuff like that so i use what makes sense to me, like it or leave it
	vec3 lightDir = normalize(sLight.position - fragPos);
	float difference = dot(lightDir, normalize(-sLight.direction));

	//Maybe change sign, idk
	if (difference > sLight.cutoff)
	{
		//We are inside! (do regular point light stuff)

		//Diffuse
		float distance = length(sLight.position - fragPos) / sLight.intensity;
		float attenuation = Attenuation(1.0, 1, 2, distance);
		float dotResult = dot(-lightDir, normal);
		vec3 diffuseColor = sLight.color * (attenuation * dotResult) * texture(uTex, iTextureCoord).rgb;

		//Specular
		vec3 reflectionDirection = reflect(-lightDir, viewDir);
		float specIntensity = dot(viewDir, reflectionDirection);
		if (specIntensity < 0) specIntensity = 0;
		specIntensity = pow(specIntensity, 32);
		specIntensity *= uSpecularity * attenuation;
		vec3 specColor = specIntensity * texture(uSpec, iTextureCoord).rgb * sLight.color;

		//Return
		return specColor + diffuseColor;
	}

	return vec3(0, 0, 0);
}
