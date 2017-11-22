#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

out vec3 col;
out vec2 textureCoord;
out vec3 norm;
out vec3 fragPos;

uniform mat4 MVPMatrix;
uniform mat4 model;

void main()
{
	gl_Position = MVPMatrix * position;
	col = color;
	textureCoord = texCoord;
	norm = mat3(transpose(inverse(model))) * normal;
	fragPos = vec3(model * position);
}

#shader fragment
#version 330 core

out vec4 color;
in vec3 col;
in vec2 textureCoord;
in vec3 norm;
in vec3 fragPos;

uniform sampler2D tex;
uniform vec3 ambient;
uniform vec3 lightPos;

void main()
{
	
	vec3 n = normalize(norm);
	vec3 l = normalize(lightPos - fragPos);
	float dif = max(dot(n, l), 0.0);

	//color = vec4(col, 1.0f);
	color = vec4((dif + ambient), 1.0) * texture(tex, textureCoord);
	//color = vec4(norm, 1.0);
	//color = texture(tex, textureCoord) * vec4(col, 1.0f);
}
