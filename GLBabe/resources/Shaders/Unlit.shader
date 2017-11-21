#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec3 col;
out vec2 textureCoord;

uniform mat4 MVPMatrix;

void main()
{
	gl_Position = MVPMatrix * position;
	col = color;
	textureCoord = texCoord;
}

#shader fragment
#version 330 core

out vec4 color;
in vec3 col;
in vec2 textureCoord;

uniform sampler2D tex;

void main()
{
	//color = vec4(col, 1.0f);
	color = texture(tex, textureCoord);
	//color = texture(tex, textureCoord) * vec4(col, 1.0f);
}