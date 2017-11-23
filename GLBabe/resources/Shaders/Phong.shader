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
uniform vec3 uAmbient;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform float uLightIntensity;
uniform vec3 uCamPos;
uniform float uSpecularity;

void main()
{
	//TODO: calc dist and multiply that by intensity to get area light

	//Diffuse
	vec3 normal = normalize(iNormal);
	vec3 lightDirection = normalize(uLightPos - iFragPos);
	float dif = dot(normal, lightDirection);
	if (dif < 0) dif = 0;

	//Specular
	vec3 viewDirection = normalize(uCamPos - iFragPos);
	vec3 reflection = reflect(-lightDirection, iNormal);
	float spec = dot(viewDirection, reflection);
	if (spec < 0) spec = 0;
	spec = pow(spec, uSpecularity);

	//Calculate simple brightness float
	float brightness = (dif + spec) * uLightIntensity;

	//Calculate color
	vec4 col = vec4(uLightColor.r, uLightColor.g, uLightColor.b, 1.0) * brightness;
	col += vec4(uAmbient, 1.0);
	col *= texture(uTex, iTextureCoord);

	//Output
	color = col;
}
