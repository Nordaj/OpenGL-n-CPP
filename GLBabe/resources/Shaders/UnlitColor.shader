#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 uMVPMatrix;

void main()
{
	gl_Position = uMVPMatrix * position;
}

#shader fragment
#version 330 core

out vec4 color;

uniform vec3 uColor;

void main()
{
	color = vec4(uColor, 1.0);
}
